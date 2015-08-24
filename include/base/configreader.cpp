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

configreader::configreader():_doc(nullptr)
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

bool configreader::load(const char* manifest_conf)
{
	if(_doc!=nullptr)
	{
		delete _doc;
		_doc = nullptr;
	}

	_doc = new tinyxml2::XMLDocument;
	if(_doc->LoadFile(manifest_conf)==XML_SUCCESS)
	{
		parse_required();
		parse_product();
		parse_path();
		parse_repository();
		parse_service();

		return true;
	}

	return false;
}

bool configreader::update(configreader* conf)
{
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
			_required.push_back(new sRequired(requiredType::COMPONENT, child->GetText(), child->Attribute("for")));
		else if(!type.compare("library"))
			_required.push_back(new sRequired(requiredType::LIBRARY, child->GetText(), child->Attribute("for")));
		else if(!type.compare("package"))
			_required.push_back(new sRequired(requiredType::PACKAGE, child->GetText(), child->Attribute("for")));
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

void configreader::parse_product()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest")->FirstChildElement("product");
	for(XMLElement* child = elem_com->FirstChildElement();child!=nullptr; child = child->NextSiblingElement())
		_product[child->Value()] = child->GetText();
}

void configreader::parse_service()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest");
	for(XMLElement* child = elem_com->FirstChildElement("service");child!=nullptr; child = child->NextSiblingElement("service"))
		_service.insert(std::pair<string, string>(child->Attribute("name"), child->GetText()));
}

} /* namespace base */
} /* namespace cossb */
