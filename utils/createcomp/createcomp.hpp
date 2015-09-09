/*
 * createcomp.hpp
 *
 *  Created on: 2015. 9. 6.
 *      Author: hwang-linux
 */

#ifndef _COSSB_UTILS_CREATECOMP_HPP_
#define _COSSB_UTILS_CREATECOMP_HPP_


#include "../../include/interface/iutility.hpp"

namespace cossb {

class createcomp : public interface::iutility {
public:
	createcomp();
	virtual ~createcomp();

	bool execute(int argc, char* argv[]);
};
} /* namespace cossb */

#endif /* _COSSB_UTILS_CREATECOMP_HPP_ */
