/*
 * libzeroconf.cpp
 *
 *  Created on: 2015. 9. 12.
 *      Author: hwang
 */

#include "libzeroconf.hpp"
#include <iostream>
#include <avahi-common/error.h>
#include <avahi-common/domain.h>
#include <algorithm>



using namespace std;

static AvahiSimplePoll* _poll = nullptr;
static AvahiClient* _client = nullptr;
static AvahiStringList* browsed_types = nullptr;
static ServiceInfo* services = nullptr;
static vector<string> _service_types;
static bool browsing = false;
static int n_columns = 80;

static ServiceInfo* find_service(AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain)
{
    ServiceInfo* i;

    for (i = services; i; i = i->info_next)
		if (i->interface == interface &&
			i->protocol == protocol &&
			strcasecmp(i->name, name) == 0 &&
			avahi_domain_equal(i->type, type) &&
			avahi_domain_equal(i->domain, domain))

			return i;

    return nullptr;
}
/**
 * @brief	add service
 */
static ServiceInfo* add_service(Config* c, AvahiIfIndex interface, AvahiProtocol protocol, const char* name, const char* type, const char* domain)
{
    ServiceInfo* i;

    i = avahi_new(ServiceInfo, 1);

    if (c->resolve) {
        if (!(i->resolver = avahi_service_resolver_new(_client, interface, protocol, name, type, domain, AVAHI_PROTO_UNSPEC, 0, service_resolver_callback, i))) {
            avahi_free(i);
            fprintf(stderr, ("Failed to resolve service '%s' of type '%s' in domain '%s': %s\n"), name, type, domain, avahi_strerror(avahi_client_errno(_client)));
            return NULL;
        }

        n_resolving++;
    } else
        i->resolver = NULL;

    i->interface = interface;
    i->protocol = protocol;
    i->name = avahi_strdup(name);
    i->type = avahi_strdup(type);
    i->domain = avahi_strdup(domain);
    i->config = c;

    AVAHI_LLIST_PREPEND(ServiceInfo, info, services, i);

    return i;
}

/**
 * @brief	remove services that found
 */
static void remove_service(Config* c, ServiceInfo* i)
{
    AVAHI_LLIST_REMOVE(ServiceInfo, info, services, i);

    if (i->resolver)
        avahi_service_resolver_free(i->resolver);

    avahi_free(i->name);
    avahi_free(i->type);
    avahi_free(i->domain);
    avahi_free(i);
}

/**
 * @brief	callback function to browse service
 */
static void service_browser_callback(
	AvahiServiceBrowser* browser,
	AvahiIfIndex interface,
	AvahiProtocol protocol,
	AvahiBrowserEvent event,
	const char *name,
	const char *type,
	const char *domain,
	AvahiLookupResultFlags flags,
	void *userdata)
{

	Config* conf = userdata;

	if(!browser || !conf)
		return;

	switch(event)
	{
		case AVAHI_BROWSER_NEW:
		{
			if(conf->ignore_local && (flags & AVAHI_LOOKUP_RESULT_LOCAL))
				break;

			if(find_service(interface, protocol, name, type, domain))
				return;

			add_service(conf, interface, protocol, name, type, domain);

			print_service_line(c, '+', interface, protocol, name, type, domain, 1);
			break;

		}

		case AVAHI_BROWSER_REMOVE: {
			ServiceInfo *info;

			if (!(info = find_service(interface, protocol, name, type, domain)))
				return;

			remove_service(c, info);

			print_service_line(c, '-', interface, protocol, name, type, domain, 1);
			break;
		}

		case AVAHI_BROWSER_FAILURE:
			fprintf(stderr, _("service_browser failed: %s\n"), avahi_strerror(avahi_client_errno(client)));
			avahi_simple_poll_quit(simple_poll);
			break;

		case AVAHI_BROWSER_CACHE_EXHAUSTED:
			n_cache_exhausted --;
			check_terminate(c);
			break;

		case AVAHI_BROWSER_ALL_FOR_NOW:
			n_all_for_now --;
			check_terminate(c);
			break;
	}
}

/**
 * @brief	browse service type in specific domain
 */
static void browse_service_type(Config *c, const char *stype, const char *domain)
{
	AvahiServiceBrowser* browser;
	AvahiStringList* i;

	for(i = browsed_types; i; i = i->next)
		if (avahi_domain_equal(stype, (char*) i->text))
			return;

	if(!(browser = avahi_service_browser_new(
			  _client,
			  AVAHI_IF_UNSPEC,
			  AVAHI_PROTO_UNSPEC,
			  stype,
			  domain,
			  0,
			  service_browser_callback,
			  c))) {

		fprintf(stderr, ("avahi_service_browser_new() failed: %s\n"), avahi_strerror(avahi_client_errno(_client)));
		avahi_simple_poll_quit(simple_poll);
	}

	browsed_types = avahi_string_list_add(browsed_types, stype);

	n_all_for_now++;
	n_cache_exhausted++;
}

/**
 * @brief	browse all services
 */
static void browse_all(Config* conf)
{
	if(!conf)
		return;

	AvahiServiceTypeBrowser* browser = nullptr;

	if(!(browser = avahi_service_type_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, conf->domain, 0, service_type_browser_callback, conf))) {

		fprintf(stderr, _("avahi_service_type_browser_new() failed: %s\n"), avahi_strerror(avahi_client_errno(client)));
		avahi_simple_poll_quit(simple_poll);
	}

	n_cache_exhausted++;
	n_all_for_now++;
}

/**
 * @brief	start to browse services with configuration
 */
static bool start(Config *config)
{
	if(config->verbose && !config->parsable)
	{
		const char *version, *hn;
		if(!(version = avahi_client_get_version_string(_client))) {
			fprintf(stderr, ("Failed to query version string: %s\n"), avahi_strerror(avahi_client_errno(_client)));
			return -1;
		}

		if(!(hn = avahi_client_get_host_name_fqdn(_client))) {
			fprintf(stderr, ("Failed to query host name: %s\n"), avahi_strerror(avahi_client_errno(_client)));
			return -1;
		}

		fprintf(stderr, ("Server version: %s; Host name: %s\n"), version, hn);

		if(config->command == COMMAND_BROWSE_DOMAINS) {
			/* Translators: This is a column heading with abbreviations for
			 *   Event (+/-), Network Interface, Protocol (IPv4/v6), Domain */
			fprintf(stderr, ("E Ifce Prot Domain\n"));
		} else {
			/* Translators: This is a column heading with abbreviations for
			 *   Event (+/-), Network Interface, Protocol (IPv4/v6), Domain */
			fprintf(stderr, ("E Ifce Prot %-*s %-20s Domain\n"), n_columns-35, ("Name"), ("Type"));
		}
	}

	if(config->command == COMMAND_BROWSE_SERVICES)
		browse_service_type(config, config->stype, config->domain);
    else if(config->command == COMMAND_BROWSE_ALL_SERVICES)
        browse_all(config);

    browsing = true;
    return true;
}


/**
 * @brief	static callback function to resolve service
 */
static void resolve_callback(
    AvahiServiceResolver* resolver,
    AVAHI_GCC_UNUSED AvahiIfIndex interface,
    AVAHI_GCC_UNUSED AvahiProtocol protocol,
    AvahiResolverEvent event,
    const char *name,
    const char *type,
    const char *domain,
    const char *host_name,
    const AvahiAddress *address,
    uint16_t port,
    AvahiStringList *txt,
    AvahiLookupResultFlags flags,
    AVAHI_GCC_UNUSED void* userdata) {

    /* Called whenever a service has been resolved successfully or timed out */

    switch (event) {
        case AVAHI_RESOLVER_FAILURE:
            fprintf(stderr, "(Resolver) Failed to resolve service '%s' of type '%s' in domain '%s': %s\n", name, type, domain, avahi_strerror(avahi_client_errno(avahi_service_resolver_get_client(resolver))));
            break;

        case AVAHI_RESOLVER_FOUND: {
            char a[AVAHI_ADDRESS_STR_MAX], *t;

            fprintf(stderr, "Service '%s' of type '%s' in domain '%s':\n", name, type, domain);

            avahi_address_snprint(a, sizeof(a), address);
            t = avahi_string_list_to_string(txt);
            fprintf(stderr,
                    "\t%s:%u (%s)\n"
                    "\tTXT=%s\n"
                    "\tcookie is %u\n"
                    "\tis_local: %i\n"
                    "\tour_own: %i\n"
                    "\twide_area: %i\n"
                    "\tmulticast: %i\n"
                    "\tcached: %i\n",
                    host_name, port, a,
                    t,
                    avahi_string_list_get_service_cookie(txt),
                    !!(flags & AVAHI_LOOKUP_RESULT_LOCAL),
                    !!(flags & AVAHI_LOOKUP_RESULT_OUR_OWN),
                    !!(flags & AVAHI_LOOKUP_RESULT_WIDE_AREA),
                    !!(flags & AVAHI_LOOKUP_RESULT_MULTICAST),
                    !!(flags & AVAHI_LOOKUP_RESULT_CACHED));

            avahi_free(t);
        }
    }

    avahi_service_resolver_free(resolver);
}

/**
 * @brief	static callback function to browse service types in domain
 */
static void type_browse_callback(
		AvahiServiceTypeBrowser* browser,
		AvahiIfIndex interface,
		AvahiProtocol protocol,
		AvahiBrowserEvent event,
		const char* type,
		const char* domain,
		AvahiLookupResultFlags flags,
		void* userdata)
{

	switch (event)
	{
		case AVAHI_BROWSER_FAILURE:
			//fprintf(stderr, "(Browser) Failed %s\n", avahi_strerror(avahi_client_errno(avahi_service_type_browser_get_client(browser))));
		{
			avahi_simple_poll_quit(_poll);
		}
			return;

		case AVAHI_BROWSER_NEW:
		{
			_service_types.push_back(type);
		}
			break;

		case AVAHI_BROWSER_REMOVE:
		{
			vector<string>::iterator itr = std::find(_service_types.begin(), _service_types.end(), type);
			if(itr!=_service_types.end())
				_service_types.erase(itr);
		}
			break;

		case AVAHI_BROWSER_ALL_FOR_NOW:
		case AVAHI_BROWSER_CACHE_EXHAUSTED:
			avahi_simple_poll_quit(_poll);
			break;
	}
}

/**
 * @brief	static callback function to browse specific service type
 */
static void browse_callback(AvahiServiceBrowser* browser,
	    AvahiIfIndex interface,
	    AvahiProtocol protocol,
	    AvahiBrowserEvent event,
	    const char* name,
	    const char* type,
	    const char* domain,
	    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
	    void* userdata) {

	AvahiClient *c = (AvahiClient*)userdata;

	/* Called whenever a new services becomes available on the LAN or is removed from the LAN */

	switch (event) {
		case AVAHI_BROWSER_FAILURE:
			fprintf(stderr, "(Browser) %s\n", avahi_strerror(avahi_client_errno(avahi_service_browser_get_client(browser))));
			avahi_simple_poll_quit(_poll);
			return;

		case AVAHI_BROWSER_NEW:
			fprintf(stderr, "(Browser) NEW: service '%s' of type '%s' in domain '%s'\n", name, type, domain);

			/* We ignore the returned resolver object. In the callback
			   function we free it. If the server is terminated before
			   the callback function is called the server will free
			   the resolver for us. */

			if (!(avahi_service_resolver_new(c, interface, protocol, name, type, domain, AVAHI_PROTO_UNSPEC, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, resolve_callback, c)))
				fprintf(stderr, "Failed to resolve service '%s': %s\n", name, avahi_strerror(avahi_client_errno(c)));

			break;

		case AVAHI_BROWSER_REMOVE:
			fprintf(stderr, "(Browser) REMOVE: service '%s' of type '%s' in domain '%s'\n", name, type, domain);
			break;

		case AVAHI_BROWSER_ALL_FOR_NOW:
		case AVAHI_BROWSER_CACHE_EXHAUSTED:
			fprintf(stderr, "(Browser) %s\n", event == AVAHI_BROWSER_CACHE_EXHAUSTED ? "CACHE_EXHAUSTED" : "ALL_FOR_NOW");
			avahi_simple_poll_quit(_poll);
			break;
	}
}

/**
 * @brief	static callback function for connection
 */
static void client_callback(AvahiClient* client, AvahiClientState state, void* userdata)
{
	Config* config = userdata;

	switch(state)
	{
	case AVAHI_CLIENT_FAILURE:
		if(config->no_fail && avahi_client_errno(client)==AVAHI_ERR_DISCONNECTED)
		{
			/* We have been disconnected, so let reconnect */
			avahi_client_free(client);
			client = nullptr;

			avahi_string_list_free(browsed_types);
			browsed_types = nullptr;

			while(services)
				remove_service(config, services);

			browsing = false;

			//retry
			int error;
			cout << "try reconnect" << endl;
			if(!(client = avahi_client_new(avahi_simple_poll_get(_poll), AVAHI_CLIENT_NO_FAIL, client_callback, config, &error)))
				avahi_simple_poll_quit(_poll);
		}
		else
		{
			fprintf(stderr, "Client failure, exiting: %s\n", avahi_strerror(avahi_client_errno(client)));
			avahi_simple_poll_quit(simple_poll);
		}
			break;

		case AVAHI_CLIENT_S_REGISTERING:
		case AVAHI_CLIENT_S_RUNNING:
		case AVAHI_CLIENT_S_COLLISION:
		{
			if(!browsing)
				if(!start(config))
					avahi_simple_poll_quit(_poll);
		}
			break;

		case AVAHI_CLIENT_CONNECTING:
			if(config->verbose && !config->parsable)
				fprintf(stderr, "Waiting for daemon ...\n");

			break;
	}
}
/**
 * @brief	callback function to browse service types in domain
 */
static void service_type_browser_callback(
    AvahiServiceTypeBrowser* browser,
    AVAHI_GCC_UNUSED AvahiIfIndex interface,
    AVAHI_GCC_UNUSED AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *type,
    const char *domain,
    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
    void *userdata)
{

	Config* conf = userdata;

	if(!browser||!conf)
		return;

	switch(event)
	{
	case AVAHI_BROWSER_NEW:
		browse_service_type(conf, type, domain);
		break;

	case AVAHI_BROWSER_REMOVE:
		/* We're dirty and never remove the browser again */
		break;

	case AVAHI_BROWSER_FAILURE:
		fprintf(stderr, _("service_type_browser failed: %s\n"), avahi_strerror(avahi_client_errno(client)));
		avahi_simple_poll_quit(simple_poll);
		break;

	case AVAHI_BROWSER_CACHE_EXHAUSTED:
		n_cache_exhausted --;
		check_terminate(c);
		break;

	case AVAHI_BROWSER_ALL_FOR_NOW:
		n_all_for_now --;
		check_terminate(c);
		break;
	}
}



vector<string> libzeroconf::get_service_types(const char* domain)
{
	return _service_types;
}



libzeroconf::libzeroconf()
{

}

libzeroconf::~libzeroconf() {
	clean();
}

void libzeroconf::clean()
{
	avahi_simple_poll_quit(_poll);

	while(services)
		remove_service(&_config, services);

	if(_client)
		avahi_client_free(_client);

	avahi_free(_config.domain);
	avahi_free(_config.stype);

	avahi_string_list_free(browsed_types);

	if(_poll)
		avahi_simple_poll_free(_poll);
}

void libzeroconf::browse(const char* domain, IProtocol ipv, event on_updated)
{
	if(!(_poll=avahi_simple_poll_new())) {
		clean();
		return;
	}

	//set configuration to browse all services in network
	_config.command = COMMAND_BROWSE_ALL_SERVICES;
	_config.verbose =
	_config.terminate_on_cache_exhausted =
	_config.terminate_on_all_for_now =
	_config.ignore_local =
	_config.resolve =
	_config.no_fail =
	_config.parsable = 0;
	_config.domain = _config.stype = nullptr;
#if defined(HAVE_GDBM) || defined(HAVE_DBM)
    c.no_db_lookup = 0;
#endif

    int error = 0;
    if(!(_client = avahi_client_new(avahi_simple_poll_get(_poll), AvahiClientFlags::AVAHI_CLIENT_NO_FAIL, client_callback, &_config, &error))) {
    	clean();
		return;
	}

    avahi_simple_poll_loop(_poll);



	//clear container
	/*_service_types.clear();

	//1. list-up service types in local network
	AvahiServiceTypeBrowser* type_browser =nullptr;
	switch(ipv)
	{
	case IPVersion::IPV4:
		type_browser = avahi_service_type_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_INET, domain, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, type_browse_callback, _client);
		break;
	case IPVersion::IPV6:
		type_browser = avahi_service_type_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_INET6, domain, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, type_browse_callback, _client);
		break;
	case IPVersion::UNSPEC:
		type_browser = avahi_service_type_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, domain, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, type_browse_callback, _client);
		break;
	}

	avahi_simple_poll_loop(_poll);
	avahi_service_type_browser_free(type_browser);

	cout << _service_types.size() << " service types was found" << endl;

	//2. list-up services in local network
	AvahiServiceBrowser* srv_browser = nullptr;
	for(auto type: _service_types)
	{
		cout << "now find " << type << " service type" << endl;
		switch(ipv)
		{
		case IPVersion::IPV4:
			srv_browser = avahi_service_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_INET, type.c_str(), domain, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, browse_callback, _client);
			break;
		case IPVersion::IPV6:
			srv_browser = avahi_service_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_INET6, type.c_str(), domain, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, browse_callback, _client);
			break;
		case IPVersion::UNSPEC:
			srv_browser = avahi_service_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, type.c_str(), domain, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, browse_callback, _client);
			break;
		}
		avahi_simple_poll_loop(_poll);
		avahi_service_browser_free(srv_browser);
	}*/
}





void libzeroconf::update_service_types()
{

}
