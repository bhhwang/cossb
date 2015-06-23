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

using namespace std;

namespace cossb {

class log : public ilog {

public:
	static log* get();
	void destroy();

private:
	static log* _instance;

};

} /* namespace cossb */

#endif /* _COSSB_LOG_HPP_ */
