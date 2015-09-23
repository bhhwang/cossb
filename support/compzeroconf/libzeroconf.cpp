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
#include <string.h>



using namespace std;

static vector<string> _service_types;

static AvahiSimplePoll* _poll = nullptr;
static AvahiClient* _client = nullptr;
static AvahiStringList* browsed_types = nullptr;
static ServiceInfo* services = nullptr;
static bool browsing = false;
static int n_columns = 80;
static int n_all_for_now = 0, n_cache_exhausted = 0, n_resolving = 0;

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

static void check_terminate(Config *c) {

    assert(n_all_for_now >= 0);
    assert(n_cache_exhausted >= 0);
    assert(n_resolving >= 0);

    if (n_all_for_now <= 0 && n_resolving <= 0) {

        if (c->verbose && !c->parsable) {
            printf((": All for now\n"));
            n_all_for_now++; /* Make sure that this event is not repeated */
        }

        if (c->terminate_on_all_for_now)
            avahi_simple_poll_quit(_poll);
    }

    if (n_cache_exhausted <= 0 && n_resolving <= 0) {

        if (c->verbose && !c->parsable) {
            printf((": Cache exhausted\n"));
            n_cache_exhausted++; /* Make sure that this event is not repeated */
        }

        if (c->terminate_on_cache_exhausted)
            avahi_simple_poll_quit(_poll);
    }
}

static void service_resolver_callback(
    AvahiServiceResolver *r,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiResolverEvent event,
    const char *name,
    const char *type,
    const char *domain,
    const char *host_name,
    const AvahiAddress *a,
    uint16_t port,
    AvahiStringList *txt,
    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
    void *userdata) {

    ServiceInfo* i = (ServiceInfo*)userdata;

    assert(r);
    assert(i);

    switch (event) {
        case AVAHI_RESOLVER_FOUND: {
            char address[AVAHI_ADDRESS_STR_MAX], *t;

            avahi_address_snprint(address, sizeof(address), a);

            t = avahi_string_list_to_string(txt);

            //print_service_line(i->config, '=', interface, protocol, name, type, domain, 0);
            fprintf(stderr, "=\t%s\t%s\t%s",name, type, domain);

            if (i->config->parsable)
                printf(";%s;%s;%u;%s\n",
                       host_name,
                       address,
                       port,
                       t);
            else
                printf("   hostname = [%s]\n"
                       "   address = [%s]\n"
                       "   port = [%u]\n"
                       "   txt = [%s]\n",
                       host_name,
                       address,
                       port,
                       t);

            avahi_free(t);

            break;
        }

        case AVAHI_RESOLVER_FAILURE:

            fprintf(stderr, ("Failed to resolve service '%s' of type '%s' in domain '%s': %s\n"), name, type, domain, avahi_strerror(avahi_client_errno(_client)));
            break;
    }


    avahi_service_resolver_free(i->resolver);
    i->resolver = NULL;

    assert(n_resolving > 0);
    n_resolving--;
    check_terminate(i->config);
    fflush(stdout);
}

/**
 * @brief	add service
 */
static ServiceInfo* add_service(Config* c, AvahiIfIndex interface, AvahiProtocol protocol, const char* name, const char* type, const char* domain)
{
    ServiceInfo* i;

    i = avahi_new(ServiceInfo, 1);

    if (c->resolve) {
        if (!(i->resolver = avahi_service_resolver_new(_client, interface, protocol, name, type, domain, AVAHI_PROTO_UNSPEC, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, service_resolver_callback, i))) {
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

	Config* conf = (Config*)userdata;

	if(!browser)
		return;

	switch(event)
	{
		case AVAHI_BROWSER_NEW:
		{
			if(conf->ignore_local && (flags & AVAHI_LOOKUP_RESULT_LOCAL))
				break;

			/*if(find_service(interface, protocol, name, type, domain))
				return;

			add_service(conf, interface, protocol, name, type, domain);*/
			cout << "+\t" << name << ":" << type << ":" << domain << endl;
		}
			break;

		case AVAHI_BROWSER_REMOVE: {
			ServiceInfo *info;

			if (!(info = find_service(interface, protocol, name, type, domain)))
				return;

			remove_service(conf, info);
			fprintf(stderr, "-\t%s\t%s\t%s",name, type, domain);
		}
			break;

		case AVAHI_BROWSER_FAILURE:
		{
			fprintf(stderr, ("service_browser failed: %s\n"), avahi_strerror(avahi_client_errno(_client)));
			avahi_simple_poll_quit(_poll);
		}
			break;

		case AVAHI_BROWSER_CACHE_EXHAUSTED:
			//n_cache_exhausted --;
			//check_terminate(conf);
			break;

		case AVAHI_BROWSER_ALL_FOR_NOW:
		{
			//n_all_for_now --;
			//check_terminate(conf);
			cout << "AVAHI_BROWSER_ALL_FOR_NOW" << endl;
		}
			break;
	}
}

/**
 * @brief	browse service type in specific domain
 */
static void browse_service_type(Config* conf, const char *stype, const char* domain)
{
	//for test
	AvahiServiceBrowser* browser = nullptr;
	auto itr = std::find(_service_types.begin(), _service_types.end(), stype);
	if(itr==_service_types.end())
	{
		_service_types.push_back(stype);
		if(_client) {
		browser = avahi_service_browser_new(_client, AVAHI_IF_UNSPEC,	AVAHI_PROTO_UNSPEC, stype, domain,
				  (AvahiLookupFlags)0, service_browser_callback,conf);
		if(!browser)
			avahi_simple_poll_quit(_poll);
		}
	}

	/*AvahiServiceBrowser* browser = nullptr;
	AvahiStringList* i = nullptr;

	for(i = browsed_types; i; i = i->next)
		if (avahi_domain_equal(stype, (char*) i->text))
			return;

	if(!(browser = avahi_service_browser_new(
			  _client,
			  AVAHI_IF_UNSPEC,
			  AVAHI_PROTO_UNSPEC,
			  stype,
			  domain,
			  AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST,
			  service_browser_callback,
			  conf))) {

		fprintf(stderr, ("avahi_service_browser_new() failed: %s\n"), avahi_strerror(avahi_client_errno(_client)));
		avahi_simple_poll_quit(_poll);
	}

	browsed_types = avahi_string_list_add(browsed_types, stype);

	n_all_for_now++;
	n_cache_exhausted++;*/
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

	Config* conf = (Config*)userdata;

	switch(event)
	{
	case AVAHI_BROWSER_NEW:
	{
		cout << "found new service type : " << avahi_proto_to_string(protocol) << ":" << type << ":" << domain << endl;
		browse_service_type(conf, type, domain);
	}
		break;

	case AVAHI_BROWSER_REMOVE:
		/* We're dirty and never remove the browser again */
		break;

	case AVAHI_BROWSER_FAILURE:
		avahi_simple_poll_quit(_poll);
		break;

	case AVAHI_BROWSER_CACHE_EXHAUSTED:
		//n_cache_exhausted --;
		//check_terminate(conf);
		break;

	case AVAHI_BROWSER_ALL_FOR_NOW:
		cout << "found " << _service_types.size() << " service types" << endl;
		//n_all_for_now --;
		//check_terminate(conf);
		break;
	}
}

/**
 * @brief	browse all services
 */
static void browse_all(Config* conf)
{
	AvahiServiceTypeBrowser* browser = avahi_service_type_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, conf->domain, (AvahiLookupFlags)0, service_type_browser_callback, conf);

	if(!browser)
		avahi_simple_poll_quit(_poll);

	//n_cache_exhausted++;
	//n_all_for_now++;
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
	Config* config = (Config*)userdata;
	_client = client;

	switch(state)
	{
	case AVAHI_CLIENT_FAILURE:
		if(config->no_fail && avahi_client_errno(client)==AVAHI_ERR_DISCONNECTED)
		{
			/* We have been disconnected, so let reconnect */
			avahi_client_free(_client);
			_client = nullptr;

			avahi_string_list_free(browsed_types);
			browsed_types = nullptr;

			while(services)
				remove_service(config, services);

			browsing = false;

			//retry
			int error;
			if(!(_client = avahi_client_new(avahi_simple_poll_get(_poll), AVAHI_CLIENT_NO_FAIL, client_callback, config, &error)))
				avahi_simple_poll_quit(_poll);
		}
		else
		{
			//fprintf(stderr, "Client failure, exiting: %s\n", avahi_strerror(avahi_client_errno(client)));
			avahi_simple_poll_quit(_poll);
		}
			break;

		case AVAHI_CLIENT_S_REGISTERING:
		case AVAHI_CLIENT_S_RUNNING:
		case AVAHI_CLIENT_S_COLLISION:
		{
			if(config->command == COMMAND_BROWSE_ALL_SERVICES)
			    browse_all(config);
			else
				avahi_simple_poll_quit(_poll);
		}
			break;

		case AVAHI_CLIENT_CONNECTING: break;
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

bool libzeroconf::browse(const char* domain, IProtocol ipv, event on_updated)
{
	if(_poll)
		return false;

	if(!(_poll=avahi_simple_poll_new())) {
		clean();
		return false;
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
    if(!(_client = avahi_client_new(avahi_simple_poll_get(_poll), _config.no_fail?AVAHI_CLIENT_NO_FAIL:(AvahiClientFlags)0, client_callback, &_config, &error))) {
    	clean();
		return false;
	}

    avahi_simple_poll_loop(_poll);

    return true;
}


void libzeroconf::update_service_types()
{

}

const char* libzeroconf::get_hostname()
{
	if(_client)
		return avahi_client_get_host_name_fqdn(_client);
	return nullptr;
}

const char* libzeroconf::get_version()
{
	if(_client)
		return avahi_client_get_version_string(_client);
	return nullptr;
}
