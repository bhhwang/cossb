/**
 * @file		icomponent.cpp
 * @brief		Component(Shared Library) interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		Component interface class
 */

#include "icomponent.hpp"

namespace cossb {
namespace interface {

icomponent::~icomponent()
{
	if(_profile)
		delete _profile;
}

const char* icomponent::get_name() const
{
	 return _name.c_str();
}

iprofile* icomponent::get_profile() const
{
	return _profile;
}

} /* namespace interface */
} /* namespace cossb */
