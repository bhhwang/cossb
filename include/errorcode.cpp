/**
 * @file		errorcode.cpp
 * @brief		Error code definitions
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	component error code definitions
 */

#include "errorcode.hpp"

namespace cossb {
namespace error {

const char* get_error_str(errorcode& e)
{
	switch(e)
	{
	case errorcode::NO_ERROR: return	"No error"; break;
	case errorcdoe::NULL_PTR: return	"Cannot access the memory";	break;
	case errorcdoe::UNPACK_FAIL: return 	"Unpacking failed";	break;
	case errorcdoe::SETUP_FAIL: return 	"Setup failed";	break;
	case errorcdoe::REGIST_FAIL: return	"Registration failed";	break;
	}
}

} /* namespace error */
} /* namespace cossb */
