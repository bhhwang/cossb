/*
 * xmlprofile.cpp
 *
 *  Created on: 2015. 6. 22.
 *      Author: hwang-linux
 */

#include "xmlprofile.hpp"

namespace cossb {
namespace profile {

xmlprofile::xmlprofile() {
	// TODO Auto-generated constructor stub

}

xmlprofile::~xmlprofile() {
	// TODO Auto-generated destructor stub
}

bool xmlprofile::load(const char* filepath)
{
	int result = _doc.LoadFile(filepath);

	if(result==XML_SUCCESS)
		_loaded = true;
	else
	{
		//this->error(result);
		_loaded = false;
	}
	return _loaded;
}

const char* xmlprofile::get_error_str(int error) const
{
	switch(error)
	{
	case	XML_NO_ATTRIBUTE: 						return "No Attribute"; 		break;
	case	XML_WRONG_ATTRIBUTE_TYPE: 				return "Wrong attribute type";	break;
	case	XML_ERROR_FILE_NOT_FOUND: 				return "Cannot found profile";	break;
	case	XML_ERROR_FILE_COULD_NOT_BE_OPENED: 	return "Profile could not be loaded";	break;
	case	XML_ERROR_ELEMENT_MISMATCH: 			return "Element mismatch";	break;
	case	XML_ERROR_PARSING_ELEMENT: 				return "Parsing element";	break;
	case	XML_ERROR_PARSING_ATTRIBUTE: 			return "Parsing attribute";	break;
	case	XML_ERROR_IDENTIFYING_TAG: 				return "Identifying tag";	break;
	case	XML_ERROR_PARSING_TEXT: 					return "Parsing text";	break;
	case	XML_ERROR_PARSING_CDATA: 				return "Parsing CDATA";	break;
	case	XML_ERROR_PARSING_COMMENT: 				return "Parsing comment";	break;
	case	XML_ERROR_PARSING_DECLARATION: 			return "Parsing declaration";	break;
	case	XML_ERROR_PARSING_UNKNOWN: 				return "Parsing unknown";	break;
	case	XML_ERROR_EMPTY_DOCUMENT: 				return "Empty document";	break;
	case	XML_ERROR_MISMATCHED_ELEMENT: 			return "Mismatched element";	break;
	case	XML_ERROR_PARSING: 						return "Parsing Error";	break;
	}
}

profile::type xmlprofile::get(profile::section section, const char* element)
{
	profile::type result;
	string section_name = "";
	bool exist = false;

	switch(section)
	{
	case profile::section::info:		section_name = "info"; exist = true;	break;
	case profile::section::property: section_name = "property";	exist = true;	break;
	case profile::section::resource: section_name = "resource";	exist = true;	break;
	default:	{ section_name = "unknown"; exist = false; }
	}


	if(_loaded && exist && _doc.FirstChildElement(section_name.c_str())!=0)
	{
		if(_doc.FirstChildElement(section_name.c_str())->FirstChildElement(element)!=0)
		{
			XMLNode* _node = _doc.FirstChildElement(section_name.c_str())->FirstChildElement(element)->FirstChild();
			if(_node)
				set(result, _node->ToText()->Value());
			/*else
				spdlog::get("main_thread")->error("Does not exist element value");*/
		}
		/*else
			spdlog::get("main_thread")->error("{} element in {} does not exist.", element, section_name);*/
	}
	/*else
		spdlog::get("main_thread")->error("Cannot find {} in the profile", section_name);*/

	return result;
}

bool xmlprofile::save()
{
	if(_loaded) {
		_doc.SaveFile(_filepath.c_str());
		return true;
	}

	return false;
}

} /* namespace profile */
} /* namespace cossb */
