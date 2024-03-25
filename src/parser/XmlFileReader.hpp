#pragma once
#include "Utility.hpp"
/// @brief Base class to encapsulate similar behavior between
// effect and emitter xml files.
class XmlFileReader
{
public:
	XmlFileReader(const std::string& path);
	XmlFileReader(const XmlFileReader&) = delete;
	virtual void parse() = 0;

protected:
	pugi::xml_document m_doc;

private:
};