/*
 * libzeroconf.cpp
 *
 *  Created on: 2015. 9. 12.
 *      Author: hwang
 */

#include "libzeroconf.hpp"
#include <iostream>
#include <avahi-common/error.h>

using namespace std;

static AvahiSimplePoll* _poll = nullptr;

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

    avahi_service_resolver_free(r);
}

void libzeroconf::type_browse_callback(AvahiServiceTypeBrowser* browser, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, const char* type, const char* domain, AvahiLookupResultFlags flags, void* userdata)
{

	switch (event)
	{
		case AVAHI_BROWSER_FAILURE:

			fprintf(stderr, "(Browser) %s\n", avahi_strerror(avahi_client_errno(avahi_service_type_browser_get_client(browser))));
			avahi_simple_poll_quit(_poll);
			return;

		case AVAHI_BROWSER_NEW:
			fprintf(stderr, "(Browser) NEW: service type '%s' in domain '%s'\n", type, domain);
			break;

		case AVAHI_BROWSER_REMOVE:
			fprintf(stderr, "(Browser) REMOVE: service type '%s' in domain '%s'\n", type, domain);
			break;

		case AVAHI_BROWSER_ALL_FOR_NOW:
		case AVAHI_BROWSER_CACHE_EXHAUSTED:
			fprintf(stderr, "(Browser) %s\n", event == AVAHI_BROWSER_CACHE_EXHAUSTED ? "CACHE_EXHAUSTED" : "ALL_FOR_NOW");
			break;
	}
}

static void browse_callback(AvahiServiceBrowser *b,
	    AvahiIfIndex interface,
	    AvahiProtocol protocol,
	    AvahiBrowserEvent event,
	    const char *name,
	    const char *type,
	    const char *domain,
	    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
	    void* userdata) {

	AvahiClient *c = (AvahiClient*)userdata;

	/* Called whenever a new services becomes available on the LAN or is removed from the LAN */

	switch (event) {
		case AVAHI_BROWSER_FAILURE:

			fprintf(stderr, "(Browser) %s\n", avahi_strerror(avahi_client_errno(avahi_service_browser_get_client(b))));
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
			break;
	}
}

static void client_callback(AvahiClient* client, AvahiClientState state, void* userdata)
{
	if(state == AVAHI_CLIENT_FAILURE)
	{
		cout << "server connection failure : " << avahi_strerror(avahi_client_errno(client)) << endl;
		avahi_simple_poll_quit(_poll);
	}
}

libzeroconf::libzeroconf() {
	// TODO Auto-generated constructor stub

}

libzeroconf::~libzeroconf() {
	// TODO Auto-generated destructor stub
}

void libzeroconf::clean()
{
	if(_browser)
		avahi_service_browser_free(_browser);

	if(_client)
		avahi_client_free(_client);

	if(_poll)
		avahi_simple_poll_free(_poll);
}

void libzeroconf::browse(const char* srv_type, const char* domain)
{
	//allocate main loop object
	if(!(_poll = avahi_simple_poll_new())) {
		cout << "Fail to create simple poll object" << endl;
		return;
	}

	//allocate new client
	int error = 0;
	_client = avahi_client_new(avahi_simple_poll_get(_poll), AvahiClientFlags::AVAHI_CLIENT_NO_FAIL, client_callback, NULL, &error);


	if(!_client) {
		cout << "Failed to create client : " << avahi_strerror(error) << endl;
		clean();
	}

	//create the service browser(for ipv4)
	if(!(_browser = avahi_service_browser_new(_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_INET, srv_type, domain, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, browse_callback, _client))) {
		cout << "Failed to create service browser : " << avahi_strerror(avahi_client_errno(_client)) << endl;
		clean();
	}

	_srv_browser = avahi_service_type_browser_new(
			_client, AVAHI_IF_UNSPEC, AVAHI_PROTO_INET, domain, AvahiLookupFlags::AVAHI_LOOKUP_USE_MULTICAST, type_browse_callback, _client);

	//run mani loop
	avahi_simple_poll_loop(_poll);
}

vector<string>* libzeroconf::get_service_types(const char* domain)
{
	return &_service_types;
}
