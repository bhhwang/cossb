/**
 * @file		compmanager.cpp
 * @brief		COSSB component manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#include "manager.hpp"
#include "container.hpp"
#include "broker.hpp"
#include "driver.hpp"

namespace cossb {
namespace manager {

bool component_manager::install(const char* component_name)
{
	if(cossb_component_container->add(component_name, new driver::component_driver(component_name)))
	{
		/*interface::icomponent* pComponent = cossb_component_container->get_component(component_name);
		if(pComponent->setup())
		{
			string publish = pComponent->get_profile()->get(profile::section::info, "publish").asString("undefined");
			cossb_component_broker->regist(pComponent,publish.c_str());
		}*/
	}
	return true;
}

types::returntype component_manager::uninstall(const char* component_name)
{
	return types::returntype::SUCCESS;
}

types::returntype component_manager::run(const char* component_name)
{
	return types::returntype::SUCCESS;
}

types::returntype component_manager::run()
{
	return types::returntype::SUCCESS;
}

types::returntype component_manager::stop(const char* component_name)
{
	return types::returntype::SUCCESS;
}

types::returntype component_manager::stop()
{
	return types::returntype::SUCCESS;
}

int component_manager::count()
{
	return 0;
}

} /* namespace manager */
} /* namespace cossb */
