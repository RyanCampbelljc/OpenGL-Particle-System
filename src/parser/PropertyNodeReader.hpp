#pragma once
#include "Utility.hpp"
#include "ValueNodeReader.hpp"
/// @brief //todo
class PropertyNodeReader
{
public:
	virtual ~PropertyNodeReader()
	{
	}
	std::string getName() const
	{
		return m_name;
	}
	ValueType getType() const
	{
		return m_type;
	}

	// todo this necessary
	// template<typename T>
	// virtual T getValue() = 0;

protected:
	PropertyNodeReader(const pugi::xml_node& node)
		: m_name(node.attribute("name").as_string())
		, m_type(ValueTypeFromString(node.attribute("type").as_string()))
	{
	}

	std::string m_name;
	ValueType m_type;
};