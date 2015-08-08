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
#include "iprofile.hpp"
#include "imessage.hpp"

using namespace std;

namespace cossb {

namespace component {
	enum class status : unsigned int { IDLE=0, RUNNING, STOPPED };
}

namespace interface {

/**
* @brief		component interface class
* @details		base component interface, lifecycle is (setup-run-stop)
* @author		Byunghun Hwang<bhhwang@nsynapse.com>
* @date		2015. 6. 22
*/
class icomponent {

public:
	/**
	 * @brief
	 */
	virtual ~icomponent() {
		if(_profile)
			delete _profile;
	}

	/**
	 * @brief		initialization
	 * @details	this function will be called once when load component
	 * @return		true if it is success
	 */
	virtual bool setup() = 0;

	/**
	 * @brief		start signal comes in, this function will be called
	 * @details
	 */
	virtual bool run() = 0;

	/**
	 * @brief	stop interface
	 * @brief	stop signal comes in, this function will be called
	 */
	virtual bool stop() = 0;

	/**
	 * @brief	message request
	 * @details	if request message comes in, this function will be called
	 */
	virtual void request(imessage* msg) = 0;

	/**
	 * @brief
	 */
	const char* get_name() const {
		return _name.c_str();
	}

	/**
	 * @brief
	 */
	iprofile* get_profile() const {
		return _profile;
	}

	/**
	 * @brief	getting status
	 */
	component::status get_status() { return _status; }

	/**
	 * @brief	set component profile
	 */
	bool set_profile(iprofile* profile, const char* path)
	{
		_profile = profile;
		return _profile->load(path);
	}


protected:
	explicit icomponent(const char* name)
	:_name(name), _profile(nullptr), _status(component::status::IDLE) {

	}

private:
	string _name;
	iprofile* _profile = nullptr;

protected:
	component::status _status;

};

} /* namespace interface */


typedef interface::icomponent*(*create_component)(void);
typedef void(*destroy_component)(void);


#define COMPONENT_EXPORT				extern "C" { cossb::interface::icomponent* create(); void destroy(void); }
#define COMPONENT_INSTANCE(classname)	static classname* _instance = nullptr;
#define COMPONENT_CREATE(classname) 	cossb::interface::icomponent* create(){ \
											if(_instance==nullptr) _instance = new classname(); \
											return _instance; }
#define COMPONENT_DESTROY 				void destroy(){ \
											if(_instance!=nullptr){ \
												delete _instance; _instance=nullptr; }	\
											}
#define COMPONENT(classname) #classname

} /* namespace cossb */


#endif /* _COSSB_ICOMPONENT_HPP_ */
