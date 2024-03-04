#pragma once
#include "Utility.hpp"
#include <type_traits>
/// @brief //todo

enum class ValueType { Invalid, Float, Vec3, Vec4 };

static ValueType ValueTypeFromString(const std::string& s)
{
	static const std::unordered_map<std::string, ValueType> valueTypeTable{
		{"float", ValueType::Float}, {"vec3", ValueType::Vec3}, {"vec4", ValueType::Vec4}};
	return valueTypeTable.at(s);
}

template<typename T>
class PropertyValue;

// need this class cause cant store list of generic types
class IPropertyValue
{
public:
	template<typename T>
	T getValue() const
	{
		return static_cast<const PropertyValue<T>*>(this)->getValue();
	}

protected:
	IPropertyValue(ValueType type)
		: m_type(type)
	{
	}

private:
	const ValueType m_type;
};

template<typename T>
class PropertyValue : public IPropertyValue
{
public:
	T getValue() const
	{
		return m_value;
	}

protected:
	PropertyValue(ValueType type, T value)
		: IPropertyValue(type)
		, m_value(value)
	{
	}
	const T m_value;
};

class FloatProperty final : public PropertyValue<float>
{
public:
	FloatProperty(const pugi::xml_node& node)
		: PropertyValue(ValueType::Float, node.text().as_float())
	{
	}
};

class Vec3Property final : public PropertyValue<glm::vec3>
{
public:
	Vec3Property(const pugi::xml_node& node)
		: PropertyValue(
			ValueType::Vec3,
			glm::vec3(
				node.child("x").text().as_float(),
				node.child("y").text().as_float(),
				node.child("z").text().as_float()))
	{
	}
};

class Vec4Property final : public PropertyValue<glm::vec4>
{
public:
	Vec4Property(const pugi::xml_node& node)
		: PropertyValue(
			ValueType::Vec4,
			glm::vec4(
				node.child("x").text().as_float(),
				node.child("y").text().as_float(),
				node.child("z").text().as_float(),
				node.child("w").text().as_float()))
	{
	}
};
