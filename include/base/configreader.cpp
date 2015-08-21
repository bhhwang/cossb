/**
 * @file		configreader.CPP
 * @brief		Config file loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load config file to run the engine
 */

#include "configreader.hpp"

namespace cossb {
namespace base {

configreader::configreader():_doc(nullptr)
{

}
configreader::~configreader()
{
	if(!_dependency.empty())
	{
		for(auto itr:_dependency)
			delete itr;
	}

	if(!_library.empty())
	{
		for(auto itr:_library)
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
		parse_dependency();
		parse_product();
		parse_path();
		parse_repository();
		parse_library();

		return true;
	}

	return false;
}

bool configreader::update(configreader* conf)
{
	return false;
}

void configreader::parse_dependency()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest");
	for(XMLElement* child = elem_com->FirstChildElement("dependency");child!=nullptr; child = child->NextSiblingElement("dependency"))
	{

		if(child->Attribute("type","package"))
			_dependency.push_back(new sDependency(dependencyType::PACKAGE, child->GetText()));
		else if(child->Attribute("type","component"))
			_dependency.push_back(new sDependency(dependencyType::COMPONENT, child->GetText()));
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

void configreader::parse_library()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest");
	for(XMLElement* child = elem_com->FirstChildElement("library");child!=nullptr; child = child->NextSiblingElement("library"))
		_library.push_back(new sLibrary(child->Attribute("use"), child->GetText()));
}

} /* namespace base */
} /* namespace cossb */
