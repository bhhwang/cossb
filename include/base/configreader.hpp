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
namespace base {

enum class requiredType : unsigned int { COMPONENT=1, LIBRARY, PACKAGE };

typedef struct _sRequired {
	requiredType type;
	std::string name;
	std::string usefor;

public:
	_sRequired(requiredType _type, string _name, string _for):type(_type),name(_name),usefor(_for) { }
	_sRequired& operator=(const _sRequired& other) { return *this; }
} sRequired;



/**
 * @brief	system configuration class
 */
class configreader : public arch::singleton<configreader> {
public:

	configreader();
	virtual ~configreader();

	/**
	 * @brief	load configuration file(manifest file)
	 */
	bool load(const char* manifest_conf);

	/**
	 * @brief	update configuration
	 */
	bool update(configreader* conf);

	/**
	 * @brief	getting manifest information
	 */
	vector<sRequired*>* get_required() { return &_required; }
	vector<string>* get_repository() { return &_repository; }
	map<string, string>* get_path() { return &_path; }
	map<string, string>* get_product() { return &_product; }
	map<string, string>* get_service() { return &_service; }

private:
	void parse_required();
	void parse_path();
	void parse_repository();
	void parse_product();
	void parse_service();


private:
	tinyxml2::XMLDocument* _doc;
	vector<sRequired*> _required;
	vector<string> _repository;
	map<string, string> _path;
	map<string, string> _product;
	map<string, string> _service;

};

#define cossb_config	cossb::base::configreader::instance()

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_CONFIG_HPP_ */
