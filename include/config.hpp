/**
 * @file		config.hpp
 * @brief		COSSB configuration Management
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load configuration file
 */

#ifndef _COSSB_CONFIG_HPP_
#define _COSSB_CONFIG_HPP_

#include <string>

using namespace std;

namespace cossb {
namespace base {

/**
 * @brief	system configuration class
 */
class config {
public:
	static config* get();
	void destroy();

	bool load(const char* manifest_conf);

	/**
	 * @brief	update configuration
	 */
	bool update(config* conf);

private:
	static config* _instance;
};

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_CONFIG_HPP_ */
