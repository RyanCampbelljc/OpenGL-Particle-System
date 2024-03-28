//-----------------------------------------------------------------------------
// File:			XmlFileReader.hpp
// Original Author:	Ryan Campbell
/// @brief Base class to encapsulate the similarities between
// emitter and effect files readers.
//-----------------------------------------------------------------------------
#pragma once
#include "Utility.hpp"

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