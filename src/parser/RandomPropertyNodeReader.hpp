#pragma once
#include "PropertyNodeReader.hpp"
#include "Utility.hpp"
class RandomPropertyNodeReader : public PropertyNodeReader
{
public:
	RandomPropertyNodeReader(const pugi::xml_node& node)
		: PropertyNodeReader(node)
		, m_min(node.child("min"), m_type)
		, m_max(node.child("max"), m_type)
	{
	}

private:
	ValueNodeReader m_min;
	ValueNodeReader m_max;
};