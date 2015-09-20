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
#include <vector>
#include <map>
#include <string>

using namespace std;

class libzeroconf {
public:
	libzeroconf();
	virtual ~libzeroconf();

	/**
	 * @brief	browse services
	 */
	void browse(const char* srv_type, const char* domain);

	/**
	 * @brief	get list of service type
	 */
	vector<string>* get_service_types(const char* domain);

private:
	void clean();

private:
	AvahiClient* _client = nullptr;
	AvahiServiceBrowser* _browser = nullptr;
	AvahiServiceTypeBrowser* _srv_browser = nullptr;

	static void type_browse_callback(AvahiServiceTypeBrowser* browser, AvahiIfIndex interface, AvahiProtocol protocol,
		    AvahiBrowserEvent event, const char* type, const char* domain, AvahiLookupResultFlags flags, void* userdata);

	vector<string> _service_types;
};

#endif /* SUPPORT_COMPZEROCONF_LIBZEROCONF_HPP_ */
