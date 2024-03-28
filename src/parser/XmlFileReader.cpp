//-----------------------------------------------------------------------------
// File:			XmlFileReader.cpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#include "XmlFileReader.hpp"

XmlFileReader::XmlFileReader(const std::string& path)
	: m_doc()
{
	auto result = m_doc.load_file(path.c_str());
	if (!result)
		throw std::exception("cannot load file");
}
