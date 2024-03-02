#include "EmitterFileReader.hpp"

EmitterFileReader::EmitterFileReader(std::string path)
	: Base(path)
{
	parse();
}

void EmitterFileReader::parse()
{
	auto emitter = m_doc.child("emitter");
	m_name = emitter.attribute("name").as_string();
	m_numParticles = emitter.attribute("num_particles").as_int();
	m_duration = emitter.attribute("duration").as_float();

	auto type = emitter.attribute("type").as_string();
	auto iter = Emitter::EmitterTypeTable.find(type);
	if (iter != Emitter::EmitterTypeTable.end()) {
		m_type = iter->second;
	} else {
		throw std::exception("Emitter type invalid");
	}

	m_spawnRate = emitter.attribute("spawn_rate").as_int();
}

const std::string& EmitterFileReader::getName() const
{
	return m_name;
}

int EmitterFileReader::getNumParticles() const
{
	return m_numParticles;
}

float EmitterFileReader::getDuration() const
{
	return m_duration;
}

Emitter::EmitterType EmitterFileReader::getType() const
{
	return m_type;
}

int EmitterFileReader::getSpawnRate() const
{
	return m_spawnRate;
}
