#pragma once
#include "PropertyNodeReader.hpp"
#include "Utility.hpp"
class ConstPropertyNodeReader : public PropertyNodeReader
{
public:
	ConstPropertyNodeReader(const pugi::xml_node& node)
		: PropertyNodeReader(node)
		, m_value(node, m_type)
	{
	}

	template<typename T>
	T getValue() const
	{
		return m_value.getValue<T>();
	}

private:
	ValueNodeReader m_value;
};