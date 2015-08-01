
#include "config.hpp"

namespace cossb {
namespace config {

sysConfig* sysConfig::_instance = nullptr;

sysConfig* sysConfig::get()
{
	if(!_instance)
		_instance = new sysConfig;
	return _instance;
}

void sysConfig::destroy()
{
	if(_instance)
		delete _instance;
}

bool sysConfig::load(const char* manifest)
{
	return false;
}

} /* namespace config */
} /* namespace cossb */
