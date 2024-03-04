#pragma once
#include "PropertyValue.hpp"
#include "Utility.hpp"
/// @brief //todo
// min,max,const_proeprty
class ValueNodeReader
{
public:
	ValueNodeReader(const ValueNodeReader&) = delete;
	ValueNodeReader(ValueNodeReader&& other)
		: m_value(std::exchange(other.m_value, nullptr))
	{
	}
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