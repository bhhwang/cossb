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
namespace service {

/**
 * @brief	service method
 */
enum class service_method : int {
	PUBLISH = 1,
	SUBSCRIBE,
};

/**
 * @brief	service description
 */
typedef struct _service_description {
	friend interface::iservice;
private:
	string name;				//service name
	service_method method;
	string topic;
} service_description;

} /* namespace service */




namespace interface {

class iservice {
public:
	iservice() { }
	virtual ~iservice() { }

	/**
	 * @brief	getting service description
	 */
	service::service_description* get_description() { return &_description; }

private:
	service::service_description	_description;

};

} /* namespace interface */

namespace service {

/**
 * @brief
 */
typedef vector<service::service_description> service_desc_container;
}

} /* namespace cossb */



#endif /* INCLUDE_INTERFACE_ISERVICE_HPP_ */
