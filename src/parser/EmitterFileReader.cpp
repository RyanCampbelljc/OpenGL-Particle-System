#include "EmitterFileReader.hpp"
#include "ConstPropertyNodeReader.hpp"
#include "RandomPropertyNodeReader.hpp"

static const char* const CONST_PROPERTY = "const_property";
static const char* const RAND_PROPERTY = "random_property";

EmitterFileReader::EmitterFileReader(std::string path)
	: Base(path)
{
	parse();
}

EmitterFileReader::~EmitterFileReader()
{
	for (const auto& kvp : m_spawnProperties) {
		delete kvp.second;
	}
}

void EmitterFileReader::parse()
{
	// todo use new reader implementation for this
	auto emitter = m_doc.child("emitter");
	m_name = emitter.attribute("name").as_string();
	m_numParticles = emitter.attribute("num_particles").as_int();
	m_duration = emitter.attribute("duration").as_float();
	m_spawnRate = emitter.attribute("spawn_rate").as_int();
	m_type = EmitterTypeFromString(emitter.attribute("type").as_string());

	for (const auto& property : emitter.child("spawn_properties").children()) {
		PropertyNodeReader* reader;
		if (std::strncmp(property.name(), CONST_PROPERTY, sizeof(CONST_PROPERTY) - 1) == 0) {
			reader = new ConstPropertyNodeReader(property);
		} else if (std::strncmp(property.name(), RAND_PROPERTY, sizeof(RAND_PROPERTY) - 1) == 0) {
			reader = new RandomPropertyNodeReader(property);
		} else {
			throw std::exception("not a valid spawn property");
		}
		m_spawnProperties[reader->getName()] = reader;
	}
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

EmitterType EmitterFileReader::getType() const
{
	return m_type;
}

int EmitterFileReader::getSpawnRate() const
{
	return m_spawnRate;
}