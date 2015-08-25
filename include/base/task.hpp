/**
 * @file		task.hpp
 * @brief		base task(thread) using boost library
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 24
 * @details	COSSB task based on Boost library
 */
#ifndef _COSSB_TASK_HPP_
#define _COSSB_TASK_HPP_

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

using namespace std;

namespace cossb {
namespace base {

typedef boost::shared_ptr<boost::thread> task;

#define create_task(fnptr)	boost::shared_ptr<boost::thread>(new task_register(&fnptr))
#define destroy_task(instance)	if(instance){ instance->interrupt(); instance->join(); }


} /* namespace base */
} /* namespace cossb */



#endif /* _COSSB_TASK_HPP_ */