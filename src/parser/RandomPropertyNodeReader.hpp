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
		// return m_max.getValue<T>();
		return Utility::randomInRange(getMax<T>(), getMin<T>());
		// if (m_type == ValueType::Float) {
		// 	return 1; // Utility::randomFloat(m_min.getValue<float>(), m_max.getValue<float>());
		// } else if (m_type == ValueType::Vec3) {
		// 	return Utility::randVec3(m_min.getValue<glm::vec3>(), m_max.getValue<glm::vec3>());
		// } else if (m_type == ValueType::Vec4) {
		// 	return Utility::randVec4(m_min.getValue<glm::vec4>(), m_max.getValue<glm::vec4>());
		// } else {
		// 	throw std::exception("invalid type on valueNodeReader");
		// }
	}

private:
	ValueNodeReader m_min;
	ValueNodeReader m_max;
};