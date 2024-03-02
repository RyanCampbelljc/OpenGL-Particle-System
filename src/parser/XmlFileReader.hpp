#pragma once
#include "Utility.hpp"

class XmlFileReader
{
public:
	XmlFileReader(std::string path);
	XmlFileReader(const XmlFileReader&) = delete;
	virtual void parse() = 0;

protected:
	pugi::xml_document m_doc;

private:
};