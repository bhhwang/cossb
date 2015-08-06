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
#include "imessage.hpp"

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
	 * @brief	stop interface
	 */
	virtual bool stop() = 0;

	/**
	 * @brief	message request
	 */
	virtual void request(imessage* msg) = 0;

	/**
	 * @brief
	 */
	const char* get_name() const;

	/**
	 * @brief
	 */
	iprofile* get_profile() const;

	/**
	 * @brief	getting status
	 */
	types::comp_status get_status() { return _status; }

	/**
	 * @brief	set component profile
	 */
	bool set_profile(iprofile* profile, const char* path)
	{
		_profile = profile;
		return _profile->load(path);
	}


protected:
	explicit icomponent(const char* name, types::comptype type)
	:_name(name), _type(type),_status(types::comp_status::READY) {

	}

private:
	string _name;
	types::comptype _type;
	iprofile* _profile = nullptr;

protected:
	types::comp_status _status;

};

} /* namespace interface */


typedef interface::icomponent*(*create_component)(void);
typedef void(*destroy_component)(void);

} /* namespace cossb */


#endif /* _COSSB_ICOMPONENT_HPP_ */
