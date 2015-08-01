

#include "instance.hpp"
#include "manager.hpp"
#include "broker.hpp"
#include "log.hpp"
#include "config.hpp"
#include "configloader.hpp"

namespace cossb {
namespace core {


bool cossb_init(base::config* config)
{
	//1. create instances for system base
	manager::system_manager::get()->setup(config);

	//2. system authentication



	return true;
}

void cossb_destroy()
{
	manager::component_manager::get()->destroy();
	broker::component_broker::get()->destroy();
}



} /* namespace core */
} /* namespace cossb */
