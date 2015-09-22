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

typedef struct Config {
    int verbose;
    int terminate_on_all_for_now;
    int terminate_on_cache_exhausted;
    char* domain;
    char* stype;
    int ignore_local;
    Command command;
    int resolve;
    int no_fail;
    int parsable;
#if defined(HAVE_GDBM) || defined(HAVE_DBM)
    int no_db_lookup;
#endif
} Config;

typedef struct ServiceInfo ServiceInfo;

struct ServiceInfo {
	AvahiIfIndex interface;
	AvahiProtocol protocol;
	char* name;
	char* type;
	char* domain;

	AvahiServiceResolver* resolver;
	Config* config;

	AVAHI_LLIST_FIELDS(ServiceInfo, info);
};

enum class IProtocol : unsigned int { IPV4=0, IPV6, UNSPEC };

class libzeroconf {
public:
	libzeroconf();
	virtual ~libzeroconf();

	/**
	 * @brief	browse services
	 */
	void browse(const char* domain, IProtocol ipv, event on_updated);


	/**
	 * @brief	get list of service type
	 */
	vector<string> get_service_types(const char* domain);

private:
	void update_service_types();


private:
	void clean();

private:
	Config _config;
	event _test = nullptr;
};

#endif /* SUPPORT_COMPZEROCONF_LIBZEROCONF_HPP_ */
