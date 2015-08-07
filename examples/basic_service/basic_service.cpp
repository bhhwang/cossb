/**
 * @file	basic_service.hpp
 * @brief	simple service component
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 8. 7
 * @details	console print component
 */


#include "../../include/interface.hpp"

using namespace cossb;

class basic_service : public interface::icomponent
{
public:
	basic_service() {};
	virtual ~basic_service() {};
};
