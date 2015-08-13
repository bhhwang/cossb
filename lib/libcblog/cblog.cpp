
#include "cblog.hpp"
#include <iostream>

namespace cossb {
namespace base {

cblog::cblog():interface::ilog(log::logstream::CONSOLE)
{

}

cblog::~cblog()
{

}

void cblog::trace(const char* logstr)
{
	cout << _time.current_formatted() << "[TRACE] " << logstr << endl;
}
void cblog::debug(const char* logstr)
{
	cout << _time.current_formatted() << "[DEBUG] " << logstr << endl;
}
void cblog::info(const char* logstr)
{
	cout << _time.current_formatted() << "[INFO] " << logstr << endl;
}
void cblog::notice(const char* logstr)
{
	cout << _time.current_formatted() << "[NOTICE] " << logstr << endl;
}
void cblog::warn(const char* logstr)
{
	cout << _time.current_formatted() << "[WARNING] " << logstr << endl;
}
void cblog::error(const char* logstr)
{
	cout << _time.current_formatted() << "[RROR] " << logstr << endl;
}
void cblog::critical(const char* logstr)
{
	cout << _time.current_formatted() << "[CRITICAL] " << logstr << endl;
}
void cblog::alert(const char* logstr)
{
	cout << _time.current_formatted() << "[ALERT] " << logstr << endl;
}
void cblog::emerg(const char* logstr)
{
	cout << _time.current_formatted() << "[EMERGENCY] " << logstr << endl;
}


} /* namespace base */



extern "C" interface::ilog* create() {
	return new base::cblog;
}

extern "C" void destroy(interface::ilog* instance) {
	delete instance;
}


} /* namespace cossb */
