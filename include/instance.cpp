

#include "instance.hpp"
#include "manager.hpp"
#include "broker.hpp"
#include "config.hpp"
#include "configloader.hpp"

#include <string>

using namespace std;

namespace cossb {
namespace core {

bool cossb_init(base::config* config)
{
	//1. create instances for system base
	if(manager::system_manager::get()->setup(config))
	{
		cout << "cossb init success" << endl;
	}

	//2. system authentication from server

	//3. repository check

	//4. access to local database

	//5. start cossb engine

	return true;
}

void cossb_destroy()
{
	//1. destroy instances
	manager::system_manager::destroy();

	//1. disconnect to servers and databases

	//2. destroy all instances
	//arch::singleton<manager::system_manager>::get()->destroy();
	//manager::component_manager::get()->destroy();
	//broker::component_broker::get()->destroy();
}

bool cossb_sync()
{
	//1. check accessibility repository

	//2. transfer information to use services

	//3. clean and update all service components

	return true;
}



} /* namespace core */
} /* namespace cossb */
