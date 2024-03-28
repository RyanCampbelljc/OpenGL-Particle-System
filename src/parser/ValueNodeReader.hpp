//-----------------------------------------------------------------------------
// File:			ValueNodeReader.hpp
// Original Author:	Ryan Campbell
/// @brief Creates the proper object to read inside an xml node depending
// on its specified type(float,vec3,vec4)
// essentially a factory pattern that makes an object to store a property value.
//-----------------------------------------------------------------------------
#pragma once
#include "PropertyValue.hpp"
#include "Utility.hpp"

class ValueNodeReader
{
public:
	ValueNodeReader(const ValueNodeReader&) = delete;

	ValueNodeReader(const pugi::xml_node& node, ValueType type)
	{
		switch (type) {
			case ValueType::Float:
				m_value = new FloatProperty(node);
				break;
			case ValueType::Vec3:
				m_value = new Vec3Property(node);
				break;
			case ValueType::Vec4:
				m_value = new Vec4Property(node);
				break;

			default:
				assert(!"invalid type");
		}
	}

	~ValueNodeReader()
	{
		delete m_value;
	}

	template<typename T>
	T getValue() const
	{
		return m_value->getValue<T>();
	}

private:
	IPropertyValue* m_value;
};