/**
 * @file		configreader.CPP
 * @brief		Config file loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load config file to run the engine
 */

#include "configreader.hpp"
#include <algorithm>

namespace cossb {
namespace base {

configreader::configreader()
{

}
configreader::~configreader()
{
	if(!_required.empty())
	{
		for(auto itr:_required)
			delete itr;
	}

	if(_doc)
		delete _doc;
}

bool configreader::load(const char* manifest_file)
{
	if(_doc!=nullptr)
	{
		delete _doc;
		_doc = nullptr;
	}

	_doc = new tinyxml2::XMLDocument;
	if(_doc->LoadFile(manifest_file)==XML_SUCCESS)
	{
		parse_required();
		parse_product_info();
		parse_path();
		parse_repository();

		return true;
	}

	return false;
}

void configreader::parse_required()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest");
	for(XMLElement* child = elem_com->FirstChildElement("required");child!=nullptr; child = child->NextSiblingElement("required"))
	{
		string type = child->Attribute("type");
		std::transform(type.begin(), type.end(), type.begin(), ::tolower);

		if(!type.compare("component"))
			_required.push_back(new conf_required(bundleType::COMPONENT, child->GetText(), child->Attribute("for")));
		else if(!type.compare("library"))
			_required.push_back(new conf_required(bundleType::LIBRARY, child->GetText(), child->Attribute("for")));
		else if(!type.compare("package"))
			_required.push_back(new conf_required(bundleType::PACKAGE, child->GetText(), child->Attribute("for")));
	}
}

void configreader::parse_path()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest")->FirstChildElement("property");
	for(XMLElement* child = elem_com->FirstChildElement("path");child!=nullptr; child = child->NextSiblingElement("path"))
		_path[child->Attribute("name")] = child->GetText();
}

void configreader::parse_repository()
{
	XMLElement* elem_uri = _doc->FirstChildElement("manifest")->FirstChildElement("repository");
	for(XMLElement* child = elem_uri->FirstChildElement("uri");child!=nullptr; child = child->NextSiblingElement("uri"))
		if(child->GetText())
			_repository.push_back(child->GetText());
}

void configreader::parse_product_info()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest")->FirstChildElement("product");
	for(XMLElement* child = elem_com->FirstChildElement();child!=nullptr; child = child->NextSiblingElement())
		_product[child->Value()] = child->GetText();
}

/*void configreader::parse_service()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest");
	for(XMLElement* child = elem_com->FirstChildElement("service");child!=nullptr; child = child->NextSiblingElement("service"))
		_service.insert(std::pair<string, string>(child->Attribute("name"), child->GetText()));
}*/

} /* namespace base */
} /* namespace cossb */
