/**
 * @file		config.hpp
 * @brief		Config file loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load config file to run the engine
 */

#ifndef _COSSB_CONFIG_HPP_
#define _COSSB_CONFIG_HPP_

#include <string>

using namespace std;

namespace cossb {

/**
* @brief	read configuration file (manifest.xml)
* @details
* @author
*/
class config {
public:
	config(const char* manifest);
	virtual ~config();

private:
	bool load(const char* file);

private:
	string _manifest_file;
};

} /* namespace cossb */

#endif /* _COSSB_CONFIG_HPP_ */
