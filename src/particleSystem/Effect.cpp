#include "Effect.hpp"
#include "parser/EffectFileReader.hpp"
Effect::Effect(std::string file)
	: m_playing(true)
{
	EffectFileReader scan(file);
	m_name = scan.getName();
	for (const auto& emitterTag : scan.getEmitterTags()) {
		// file val is correct here but not in emitter constructor
		// todo emplace back wouldnt work here -> memory violation
		Emitter e(emitterTag.file, emitterTag.offset);
		m_emitters.push_back(e);
	}
}

void Effect::play()
{
	m_playing = true;
}

void Effect::stop()
{
	pause();
	seek(0);
}

void Effect::pause()
{
	m_playing = false;
}

void Effect::seek(float time)
{
	for (const auto& emitter : m_emitters) {
		// emitter.setTime(0) or soemthing
	}
}

void Effect::setTransform(const glm::mat4& transform)
{
	m_transform = transform;
}

void Effect::update(float dt)
{
	m_dt = dt;
	if (!m_playing)
		return;
	for (auto& emitter : m_emitters) {
		emitter.update(dt);
	}
}

void Effect::render() const
{
	for (const auto& emitter : m_emitters) {
		emitter.render(m_transform);
	}
}

void Effect::toString() const
{
	std::cout << "Effect: "
			  << "name: " << m_name << std::endl;
	for (const auto& emitter : m_emitters) {
		std::cout << "	" << emitter << std::endl;
	}
}
