/**
 * @file	Find process by name
 */

#ifndef _COSSB_BASE_PID_H_
#define _COSSB_BASE_PID_H_

namespace cossb {
namespace util {

#ifndef _cplusplus
extern "C"
{
#endif


/**
 * @brief	get pid by name
 */
extern int get_pid(const char* processname);

#ifndef _cplusplus
}
#endif


} /*  */
} /* namespace cossb */

#endif /* _COSSB_BASE_PID_H_ */
