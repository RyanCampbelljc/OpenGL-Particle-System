#include "XmlFileReader.hpp"

// todo const?
XmlFileReader::XmlFileReader(std::string path)
	: m_doc()
{
	auto result = m_doc.load_file(path.c_str());
	if (!result)
		throw std::exception("cannot load file");
	// todo cannot put parse here as its undefined unless called from a defined function?
	// parse();
}
