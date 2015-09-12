/**
 * @file		compzeroconf.hpp
 * @brief		Zero Configuration Component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 9. 12
 * @details	Zero Configuration component for COSSB
 */

#ifndef SUPPORT_COMPZEROCONF_COMPZEROCONF_HPP_
#define SUPPORT_COMPZEROCONF_COMPZEROCONF_HPP_

#include "../../include/interface.hpp"

using namespace cossb;
class libzeroconf;
class compzeroconf : public interface::icomponent {
public:
	compzeroconf();
	virtual ~compzeroconf();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);

private:
	libzeroconf* _zeroconf = nullptr;

};

COMPONENT_EXPORT

#endif /* SUPPORT_COMPZEROCONF_COMPZEROCONF_HPP_ */
