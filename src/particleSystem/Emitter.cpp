#include "Emitter.hpp"
#include "parser/EmitterFileReader.hpp"

EmitterType EmitterTypeFromString(const std::string& s)
{
	static const std::unordered_map<std::string, EmitterType> emitterTypeTable = {
		{"continuous", EmitterType::continuous}, {"burst", EmitterType::burst}};
	return emitterTypeTable.at(s);
}

Emitter::Emitter(std::string file, glm::vec3 offset)
	: m_offset(offset)
{
	// todo file is empty
	EmitterFileReader scan(file);
	m_name = scan.getName();
	m_numParticles = scan.getNumParticles();
	m_duration = scan.getDuration();
	m_type = scan.getType();
	m_spawnRate = scan.getSpawnRate();
	m_spawnProperties = scan.getSpawnProperties();
	auto x = m_spawnProperties.at("size");
}

void Emitter::init()
{
}

void Emitter::render(glm::mat4 transform) const
{
}

void Emitter::update(float dt)
{
}

void Emitter::addToPool(Particle* p)
{
	p->prev = nullptr;
}

Emitter::Particle* Emitter::getFreeParticle()
{
	return new Particle;
}

void Emitter::spawnParticle()
{
}

void Emitter::particleKilled(Particle* p)
{
}

std::ostream& operator<<(std::ostream& os, const Emitter& emitter)
{
	os << "Emitter: "
	   << "name: " << emitter.getName() << "; num particles: " << emitter.getNumParticles()
	   << "; duration: " << emitter.getDuration() << "; type: " << (int)emitter.getType()
	   << "; spawn rate: " << emitter.getSpawnRate();
	return os;
}