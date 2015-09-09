
#include "compmdns.hpp"
#include "../../include/componentpack.hpp"

COMPONENT_INSTANCE(compmdns)
COMPONENT_CREATE(compmdns)
COMPONENT_DESTROY

compmdns::compmdns()
:interface::icomponent(COMPONENT(compmdns))
{
	// TODO Auto-generated constructor stub

}

compmdns::~compmdns() {
	// TODO Auto-generated destructor stub
}

bool compmdns::setup()
{
	return true;
}

bool compmdns::run()
{
	return true;
}

bool compmdns::stop()
{
	return true;
}

void compmdns::request(cossb::message::message* msg)
{

}
