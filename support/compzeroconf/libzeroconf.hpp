/**
 * @file		libzeroconf.hpp
 * @brief		Zero Configuration Impl. using Avahi
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 9. 12
 * @details	Zero Configuration wrapper class using Avahi
 */

#ifndef SUPPORT_COMPZEROCONF_LIBZEROCONF_HPP_
#define SUPPORT_COMPZEROCONF_LIBZEROCONF_HPP_

#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-common/simple-watch.h>
#include <avahi-common/malloc.h>
#include <avahi-common/llist.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

typedef void (*event)(void);
typedef enum {
    COMMAND_HELP,
    COMMAND_VERSION,
    COMMAND_BROWSE_SERVICES,
    COMMAND_BROWSE_ALL_SERVICES,
    COMMAND_BROWSE_DOMAINS
#if defined(HAVE_GDBM) || defined(HAVE_DBM)
    , COMMAND_DUMP_STDB
#endif
} Command;

enum class IProtocol : int { IPV4=0, IPV6, UNSPEC=-1 };

typedef struct Config {
    int verbose;
    int terminate_on_all_for_now;
    int terminate_on_cache_exhausted;
    char* domain;
    char* stype;
    int ignore_local;
    Command command;
    AvahiProtocol protocol;
    int resolve;
    int no_fail;
    int parsable;
#if defined(HAVE_GDBM) || defined(HAVE_DBM)
    int no_db_lookup;
#endif
} Config;

/*typedef struct ServiceInfo ServiceInfo;

struct ServiceInfo {
	AvahiIfIndex interface;
	AvahiProtocol protocol;
	char* name;
	char* type;
	char* domain;

	AvahiServiceResolver* resolver;
	Config* config;

	AVAHI_LLIST_FIELDS(ServiceInfo, info);
};*/

typedef struct ServiceInfo	ServiceInfo;
struct ServiceInfo {
	string name;
	string type;
	string domain;
	IProtocol protocol;
};

class libzeroconf {
public:
	libzeroconf();
	virtual ~libzeroconf();

	/**
	 * @brief	browse services
	 * @detail	all services will be browsed.
	 * @return	return false if it is failed.
	 */
	bool browse(const char* domain, IProtocol ipv, event on_change);


	/**
	 * @brief	get list of service type
	 */
	vector<string> get_service_types(const char* domain);

private:
	void update_service_types();

private:

	/**
	 * @brief	setup for zero config
	 */
	void setup(const char* domain, IProtocol ipv);

	/**
	 * @brief	shutdown for zero config
	 */
	void shutdown();

private:
	/**
	 * @brief	avahi callback functions
	 */
	static void client_callback(AvahiClient* client, AvahiClientState state, void* userdata);
	static void service_type_browser_callback(
	    AvahiServiceTypeBrowser* browser,
	    AVAHI_GCC_UNUSED AvahiIfIndex interface,
	    AVAHI_GCC_UNUSED AvahiProtocol protocol,
	    AvahiBrowserEvent event,
	    const char *type,
	    const char *domain,
	    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
	    void *userdata);

	static void service_browser_callback(
		AvahiServiceBrowser* browser,
		AvahiIfIndex interface,
		AvahiProtocol protocol,
		AvahiBrowserEvent event,
		const char *name,
		const char *type,
		const char *domain,
		AvahiLookupResultFlags flags,
		void *userdata);

private:
	Config _config;
};

#endif /* SUPPORT_COMPZEROCONF_LIBZEROCONF_HPP_ */
