/**
 * @file		config.CPP
 * @brief		Config file loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load config file to run the engine
 */

#include "config.hpp"

namespace cossb {

config::config(const char* manifest):_manifest_file(manifest) {

}

config::~config() {
	// TODO Auto-generated destructor stub
}

bool config::load(const char* file)
{
	return false;
}

} /* namespace cossb */
