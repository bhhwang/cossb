/**
 * @file		icomponent.hpp
 * @brief		Component(Shared Library) interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		Component interface class
 */

#ifndef _COSSB_ICOMPONENT_HPP_
#define _COSSB_ICOMPONENT_HPP_

#include <string>
#include "../typedef.hpp"

using namespace std;

namespace cossb {
namespace interface {

/**
* @brief		component interface class
* @details		base component interface, lifecycle is (setup-run-stop)
* @author		Byunghun Hwang<bhhwang@nsynapse.com>
* @date		2015. 6. 22
*/
class icomponent {

public:
	virtual ~icomponent() = 0;

	/**
	 * @brief		initialization
	 * @return		true if it is success
	 */
	virtual bool setup() = 0;

	/**
	 * @brief		work process logic (loop)
	 */
	virtual bool run() = 0;

	/**
	 * @brief
	 */
	const char* get_name() { return _name.c_str(); }


protected:
	explicit icomponent(const char* name):_name(name) {

	}

private:
	string _name;

};

} /* namespace interface */


typedef interface::icomponent*(*create_component)(void);
typedef void(*destroy_component)(void);

} /* namespace cossb */


#endif /* _COSSB_ICOMPONENT_HPP_ */
