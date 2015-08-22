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

enum class dependencyType : unsigned int { COMPONENT=1, PACKAGE };

typedef struct _sDependency {
	dependencyType type;
	std::string name;

public:
	_sDependency(dependencyType _type, string _name):type(_type),name(_name) { }
	_sDependency& operator=(const _sDependency& other) { return *this; }
} sDependency;

typedef struct _sLibrary {
	std::string use;
	std::string sofile;
public:
	_sLibrary(string _use, string _sofile):use(_use), sofile(_sofile) { }
} sLibrary;



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
	vector<sDependency*>* get_dependency() { return &_dependency; };
	vector<string>* get_repository() { return &_repository; }
	vector<sLibrary*>* get_library() { return &_library; }
	map<string, string>* get_path() { return &_path; }
	map<string, string>* get_product() { return &_product; }
	map<string, string>* get_service() { return &_service; }

private:
	void parse_dependency();
	void parse_path();
	void parse_repository();
	void parse_product();
	void parse_library();
	void parse_service();


private:
	tinyxml2::XMLDocument* _doc;
	vector<sDependency*> _dependency;
	vector<string> _repository;
	vector<sLibrary*> _library;
	map<string, string> _path;
	map<string, string> _product;
	map<string, string> _service;

};

#define cossb_config	cossb::base::configreader::instance()

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_CONFIG_HPP_ */
