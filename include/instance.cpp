

#include "instance.hpp"
#include "manager.hpp"
#include "broker.hpp"
#include "config.hpp"

#include <string>

using namespace std;

namespace cossb {
namespace core {

bool cossb_init(const char* manifest)
{
	//1. load manifest file
	if(!cossb_config->load(manifest))
		return false;

	//2. create(setup) instances according to the manifest
	if(!cossb_system_manager->setup(base::config::instance()))
		return false;

	return true;
}

void cossb_destroy()
{
	base::config::destroy();
	manager::system_manager::destroy();
}

bool cossb_sync()
{
	return true;
}


bool cossb_start()
{
	if(cossb_component_manager->run()==types::returntype::SUCCESS)
		return true;

	return false;
}

bool cossb_stop()
{
	if(cossb_component_manager->stop()==types::returntype::SUCCESS)
		return true;

	return false;
}



} /* namespace core */
} /* namespace cossb */
