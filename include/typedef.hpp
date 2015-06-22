/**
 * @file		typedef.hpp
 * @brief		COSSB Type definitions
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#ifndef _COSSB_TYPEDEF_HPP_
#define _COSSB_TYPEDEF_HPP_


#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost;

namespace cossb {


namespace process {
	typedef boost::shared_ptr<boost::thread> task;

	#define task_register(fnptr)	boost::thread(boost::bind(fnptr, this))
	#define create_task(fnptr)	boost::shared_ptr<boost::thread>(new task_register(&fnptr))
	#define destroy_task(instance)	if(instance){ instance->interrupt(); instance->join(); }
}

namespace types {

	#define COMPONENT_EXT	".comp"
	#define PROFILE_EXT		".xml"

	enum class comptype : unsigned int { SERVICE=0, APP };
	enum class comp_status : unsigned int { READY = 0, RUNNING, STOPPED };
	enum class return_type : int { EXIST=-1, FAIL=0, SUCCESS=1 };


} /* namespace types */
} /* namespace cossb */


#endif /* _COSSB_TYPEDEF_HPP_ */
