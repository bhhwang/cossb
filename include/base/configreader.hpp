/**
 * @file		configreader.hpp
 * @brief		COSSB configuration Reader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load(Read) configuration file
 */

#ifndef _COSSB_CONFIG_HPP_
#define _COSSB_CONFIG_HPP_

#include "../arch/singleton.hpp"
#include <tinyxml2.h>
#include <vector>
#include <string>
#include <map>

using namespace tinyxml2;
using namespace std;

namespace cossb {
namespace driver { class component_driver; }
namespace broker { class component_broker; }

namespace base {

enum class bundleType : unsigned int { COMPONENT=1, LIBRARY, PACKAGE };

typedef struct _conf_required {
	bundleType type;
	std::string name;
	std::string usefor;

public:
	_conf_required(bundleType _type, string _name, string _for):type(_type),name(_name),usefor(_for) { }
	_conf_required& operator=(const _conf_required& other) { return *this; }
} conf_required;



/**
 * @brief	system configuration class
 */
class configreader : public arch::singleton<configreader> {

	friend class driver::component_driver;
	friend class broker::component_broker;

public:
	configreader();
	virtual ~configreader();

	/**
	 * @brief	load configuration file(manifest file)
	 */
	bool load(const char* manifest_file);

	/**
	 * @brief	getting manifest information
	 */
	vector<conf_required*>& get_required() { return _required; }

	/**
	 * @brief	getting manifest repository
	 */
	vector<string>& get_repository() { return _repository; }

	/**
	 * @brief	getting path property
	 */
	map<string, string>& get_path() { return _path; }

	/**
	 * @brief	getting product information
	 */
	map<string, string>& get_product_info() { return _product; }

private:
	void parse_required();
	void parse_path();
	void parse_repository();

	/**
	 * @brief	parse product information from manifest file
	 */
	void parse_product_info();


private:
	/**
	 * @brief	xml manifest document
	 */
	tinyxml2::XMLDocument* _doc = nullptr;

	vector<conf_required*> _required;
	vector<string> _repository;
	map<string, string> _path;
	map<string, string> _product;

};

#define cossb_config		cossb::base::configreader::instance()

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_CONFIG_HPP_ */
