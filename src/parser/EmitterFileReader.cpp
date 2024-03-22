#include "EmitterFileReader.hpp"
#include "ConstPropertyNodeReader.hpp"
#include "RandomPropertyNodeReader.hpp"
#include "affectors/ColorLerpAffector.hpp"
#include "affectors/FadeAffector.hpp"
#include "affectors/ScaleAffector.hpp"
#include "affectors/VelocityAffector.hpp"
static const char* const CONST_PROPERTY = "const_property";
static const char* const RAND_PROPERTY = "random_property";

EmitterFileReader::EmitterFileReader(std::string path)
	: Base(path)
{
	parse();
}

EmitterFileReader::~EmitterFileReader()
{
	// for (const auto& kvp : m_spawnProperties) {
	// 	delete kvp.second;
	// }
}

// use shared pointer so when the reader goes out of scope(when the emitter constructor finishes)
// the emitter class can still have a shared pointer member pointing to the data
// todo have these string comaprisions in const char * 's
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
		std::shared_ptr<PropertyNodeReader> reader;
		if (std::strncmp(property.name(), CONST_PROPERTY, sizeof(CONST_PROPERTY) - 1) == 0) {
			reader = std::make_shared<ConstPropertyNodeReader>(property);
		} else if (std::strncmp(property.name(), RAND_PROPERTY, sizeof(RAND_PROPERTY) - 1) == 0) {
			reader = std::make_shared<RandomPropertyNodeReader>(property);
		} else {
			throw std::exception("not a valid spawn property");
		}
		m_spawnProperties[reader->getName()] = reader;
	}

	for (const auto& affectorNode : emitter.child("affectors").children()) {
		auto affectorName = affectorNode.attribute("name").as_string();
		if (std::strncmp(affectorName, "velocity", 8) == 0)
			m_affectors.push_back(std::make_shared<VelocityAffector>());
		else if (std::strncmp(affectorName, "fade", 4) == 0) {
			auto end = affectorNode.child("end").text().as_float();
			m_affectors.push_back(std::make_shared<FadeAffector>(end));
		} else if (std::strncmp(affectorName, "scale", 5) == 0) {
			auto end = affectorNode.child("end").text().as_float();
			m_affectors.push_back(std::make_shared<ScaleAffector>(end));
		} else if (std::strncmp(affectorName, "color", 5) == 0) {
			auto endTag = affectorNode.child("end");
			auto val = ValueNodeReader(endTag, ValueType::Vec3).getValue<glm::vec3>();
			m_affectors.push_back(std::make_shared<ColorLerpAffector>(val));
		} else {
			throw std::exception("not a valid affector");
		}
	}

	for (const auto& materialProperty : emitter.child("material").children()) {
		auto propName = materialProperty.name();
		if (std::strncmp(propName, "texture", 7) == 0)
			m_textureFilePath = materialProperty.text().as_string();
		else if (std::strncmp(propName, "blend_mode", 10) == 0) {
			for (const auto& blendProp : materialProperty.children()) { // looping through 4 blend modes
				auto blendValue = blendProp.text().as_string();
				m_blendModes.push_back(blendValue);
			}
		}
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

std::unordered_map<std::string, std::shared_ptr<PropertyNodeReader>> EmitterFileReader::getSpawnProperties() const
{
	return m_spawnProperties;
}

std::vector<std::shared_ptr<BaseAffector>> EmitterFileReader::getAffectors() const
{
	return m_affectors;
}

const std::string& EmitterFileReader::getTexturePath() const
{
	return m_textureFilePath;
}

std::vector<std::string> EmitterFileReader::getBlendModes() const
{
	return m_blendModes;
}