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
#include "iprofile.hpp"

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
	virtual ~icomponent();

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
	const char* get_name() const;

	/**
	 * @brief
	 */
	iprofile* get_profile() const;

	/**
	 * @brief	set component profile
	 */
	bool set_profile(iprofile* profile, const char* path)
	{
		_profile = profile;
		return _profile->load(path);
	}


protected:
	explicit icomponent(const char* name, types::comptype type):_name(name), _type(type) {

	}

private:
	string _name;
	types::comptype _type;
	iprofile* _profile = nullptr;

};

} /* namespace interface */


typedef interface::icomponent*(*create_component)(void);
typedef void(*destroy_component)(void);

} /* namespace cossb */


#endif /* _COSSB_ICOMPONENT_HPP_ */
