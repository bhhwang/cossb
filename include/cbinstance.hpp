/**
 * @file		cbinstance.hpp
 * @brief		COSSB instance
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 27
 * @details	COSSB Instance
 */

#ifndef _COSSB_CBINSTANCE_HPP_
#define _COSSB_CBINSTANCE_HPP_

namespace cossb {

#ifndef _cplusplus
extern "C" {
#endif

/**
 * @brief create COSSB core instances
 */
void cossb_init();

/**
 * @brief destroy COSSB core instances
 */
void cossb_destroy();


#ifndef _cplusplus
}
#endif

} /* namespace cossb */

#endif /* _COSSB_BASE_CBINSTANCE_HPP_ */
