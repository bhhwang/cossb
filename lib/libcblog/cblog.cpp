
#include "cblog.hpp"
#include <iostream>

using namespace std;

namespace cossb {
namespace base {

cblog::cblog():interface::ilog(log::logstream::CONSOLE)
{

}

cblog::~cblog()
{

}

void cblog::log(const log::loglevel& level, const char* logstr)
{
	switch(level)
	{
	case	log::loglevel::TRACE:	cout << _time.current_formatted() << "[TRACE] " << logstr << endl;	break;
	case	log::loglevel::DEBUG:	cout << _time.current_formatted() << "[DEBUG] " << logstr << endl;	break;
	case	log::loglevel::INFO:	cout << _time.current_formatted() << "[INFO] " << logstr << endl;	break;
	case	log::loglevel::NOTICE:  cout << _time.current_formatted() << "[NOTICE] " << logstr << endl;	break;
	case	log::loglevel::WARN: 	cout << _time.current_formatted() << "[WARNING] " << logstr << endl;	break;
	case	log::loglevel::ERROR: cout << _time.current_formatted() << "[ERROR] " << logstr << endl;	break;
	case	log::loglevel::CRITICAL: cout << _time.current_formatted() << "[CRITICAL] " << logstr << endl;	break;
	case	log::loglevel::ALERT: cout << _time.current_formatted() << "[ALERT] " << logstr << endl;	break;
	case	log::loglevel::EMERG: cout << _time.current_formatted() << "[EMERGENCY] " << logstr << endl;	break;
	}
}


} /* namespace base */



extern "C" interface::ilog* create() {
	return new base::cblog;
}

extern "C" void destroy(interface::ilog* instance) {
	delete instance;
}


} /* namespace cossb */
