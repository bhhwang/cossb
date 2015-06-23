/**
 * @file		log.hpp
 * @brief		log handler
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	log handler
 */

#ifndef _COSSB_LOG_HPP_
#define _COSSB_LOG_HPP_

#include <string>
#include "interface/ilog.hpp"

using namespace std;

namespace cossb {
namespace log {

class log : public interface::ilog {

public:
	static log* get();
	void destroy();

private:
	static log* _instance;

};

} /* namespace log */
} /* namespace cossb */

#endif /* _COSSB_LOG_HPP_ */
