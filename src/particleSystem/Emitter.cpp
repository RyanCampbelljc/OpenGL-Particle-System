#include "Emitter.hpp"
#include "parser/EmitterFileReader.hpp"

std::unordered_map<std::string, Emitter::EmitterType> const Emitter::EmitterTypeTable = {
	{"continuous", EmitterType::continuous},
	{"burst", EmitterType::burst}};

Emitter::Emitter(std::string file, glm::vec3 offset)
	: m_file(file)
	, m_offset(offset)
{
	// todo file is empty
	EmitterFileReader scan(m_file);
	m_name = scan.getName();
	m_numParticles = scan.getNumParticles();
	m_duration = scan.getDuration();
	m_type = scan.getType();
	m_spawnRate = scan.getSpawnRate();
}

void Emitter::toString() const
{
	std::cout << "Emitter: "
			  << "name: " << m_name << "; num particles: " << m_numParticles << "; duration: " << m_duration
			  << "; type: " << m_type << "; spawn rate: " << m_spawnRate << std::endl;
}