/*
 * iservice.hpp
 *
 *  Created on: 2015. 10. 13.
 *      Author: hwang
 */

#ifndef INCLUDE_INTERFACE_ISERVICE_HPP_
#define INCLUDE_INTERFACE_ISERVICE_HPP_

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


namespace cossb {
namespace interface { class iservice; }

namespace interface {

class iservice {
public:
	iservice() { }
	virtual ~iservice() { }

	/**
	 * @brief	getting service description
	 */
	//service::service_description* get_description() { return &_description; }

private:
	//service::service_description	_description;

};

} /* namespace interface */

namespace service {

/**
 * @brief
 */
//typedef vector<service::service_description*> service_desc_container;
}

} /* namespace cossb */



#endif /* INCLUDE_INTERFACE_ISERVICE_HPP_ */
