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

private:
	void clean();

private:
	AvahiClient* _client = nullptr;
	AvahiServiceBrowser* _browser = nullptr;
	AvahiServiceTypeBrowser* _srv_browser = nullptr;
};

#endif /* SUPPORT_COMPZEROCONF_LIBZEROCONF_HPP_ */
