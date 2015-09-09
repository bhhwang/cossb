/**
 * @file		instance.hpp
 * @brief		COSSB Instance
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 27
 * @details	COSSB Instance
 */

#ifndef _COSSB_INSTANCE_HPP_
#define _COSSB_INSTANCE_HPP_

#include "base/configreader.hpp"

namespace cossb {
namespace core {

#ifndef _cplusplus
extern "C" {
#endif

/**
 * @brief create COSSB core instances
 */
extern bool cossb_init(const char* manifest, bool setup=true);

/**
 * @brief destroy COSSB core instances
 */
extern void cossb_destroy();

/**
 * @brief	service components synchronization
 */
extern bool cossb_sync();

/**
 * @brief	start COSSB engine
 */
extern bool cossb_start();

/**
 * @brief	stop COSSB Engine
 */
extern bool cossb_stop();


#ifndef _cplusplus
}
#endif

} /* namespace core */
} /* namespace cossb */

#endif /* _COSSB_INSTANCE_HPP_ */
