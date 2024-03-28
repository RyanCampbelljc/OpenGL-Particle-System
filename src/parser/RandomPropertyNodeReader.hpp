//-----------------------------------------------------------------------------
// File:			RandomPropertyNodeReader.hpp
// Original Author:	Ryan Campbell
/// @brief Reads in information of a random spawn property.
//-----------------------------------------------------------------------------
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

	template<typename T>
	T getMin() const
	{
		return m_min.getValue<T>();
	}

	template<typename T>
	T getMax() const
	{
		return m_max.getValue<T>();
	}

	template<typename T>
	T getValue() const
	{
		return Utility::randomInRange(getMax<T>(), getMin<T>());
	}

private:
	ValueNodeReader m_min;
	ValueNodeReader m_max;
};