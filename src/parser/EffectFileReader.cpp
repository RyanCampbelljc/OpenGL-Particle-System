#include "EffectFileReader.hpp"

static const char* const EMITTER_TAG_NAME = "emitter";
EffectFileReader::EffectFileReader(std::string path)
	: Base(path)
{
	parse();
}

void EffectFileReader::parse()
{
	auto effect = m_doc.child("effect");
	m_name = effect.attribute("name").as_string();

	for (const auto& tag : effect) {
		if (std::strncmp(tag.name(), EMITTER_TAG_NAME, sizeof(EMITTER_TAG_NAME) - 1) != 0) {
			continue;
		}
		std::string file = tag.attribute("file").as_string();
		auto x = tag.attribute("x").as_float();
		auto y = tag.attribute("y").as_float();
		auto z = tag.attribute("z").as_float();
		m_emitters.emplace_back(file, glm::vec3(x, y, z));
	}
}

const std::string& EffectFileReader::getName() const
{
	return m_name;
}

const std::vector<EffectFileReader::EmitterTag>& EffectFileReader::getEmitterTags() const
{
	return m_emitters;
}
