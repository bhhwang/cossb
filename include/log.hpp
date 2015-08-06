/*
 * log.hpp
 *
 *  Created on: 2015. 8. 5.
 *      Author: hwang-linux
 */

#ifndef INCLUDE_LOG_HPP_
#define INCLUDE_LOG_HPP_

namespace cossb {
namespace base {

class log : public interface::ilog {
public:
	log();
	virtual ~log();

	void log(const char* logstr);
};

} /* namespace base */
} /* namespace cossb */

#endif /* INCLUDE_LOG_HPP_ */
