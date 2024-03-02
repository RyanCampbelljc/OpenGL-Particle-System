#pragma once
#include "Utility.hpp"
#include "unordered_map"
class Emitter
{
public:
	enum EmitterType { continuous, burst };
	// used to convert string to enum in parser
	static std::unordered_map<std::string, EmitterType> const EmitterTypeTable;
	Emitter(std::string file, glm::vec3 offset);
	void toString() const;
	// render
	// update

private:
	std::string m_file;
	glm::vec3 m_offset;
	std::string m_name;
	int m_numParticles;
	float m_duration;
	EmitterType m_type;
	int m_spawnRate;
	// still need spawn properties(struct?)
	// still need affectorList();
	// list of particles
	// vbo/ vao/ material for each emitter
};

/**
 * PLAN
 *
 */