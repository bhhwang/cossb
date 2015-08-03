/**
 * @file		configloader.hpp
 * @brief		Config file loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load config file to run the engine
 */

#ifndef _COSSB_CONFIGLOADER_HPP_
#define _COSSB_CONFIGLOADER_HPP_

namespace cossb {
namespace base {

class config;
class configloader {
public:
	configloader();
	virtual ~configloader();

	bool load(config* conf);
	config* load(const char* configpath);

};


} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_CONFIGLOADER_HPP_ */
