#include "Effect.hpp"
#include "parser/EffectFileReader.hpp"

Effect::Effect(std::string file)
	: m_playing(true)
	, m_position(glm::vec3(0.0f, 0.0f, 0.0f))
	, m_scale(glm::vec3(1.0f, 1.0f, 1.0f))
	, m_rotation(glm::vec3(0.0f, 0.0f, 0.0f))
{
	EffectFileReader scan(file);
	m_name = scan.getName();
	for (const auto& emitterTag : scan.getEmitterTags()) {
		// use new cause cpp likes to move and deconstruct stuff leading to bugs and not tell me.
		m_emitters.push_back(std::make_shared<Emitter>(emitterTag.file, emitterTag.offset));
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

void Effect::setPosition(const glm::vec3& pos)
{
	m_position = pos;
	updateTransfrom();
}

void Effect::setscale(const glm::vec3& scale)
{
	m_scale = scale;
	updateTransfrom();
}

void Effect::setrotation(const glm::vec3& rot)
{
	m_rotation = rot;
	updateTransfrom();
}

void Effect::update(float dt)
{
	m_dt = dt;
	if (!m_playing)
		return;
	for (auto& emitter : m_emitters) {
		emitter->update(dt);
	}
}

void Effect::render(const Camera::CamParams& params) const
{
	for (const auto& emitter : m_emitters) {
		emitter->render(params, m_transform);
	}
}

void Effect::resetEffect()
{
	for (const auto& emitter : m_emitters) {
		emitter->resetEmitter();
	}
}

void Effect::updateTransfrom()
{
	m_transform = glm::translate(glm::mat4(1.0f), m_position);
	m_transform = glm::rotate(m_transform, m_rotation.x, glm::vec3(1, 0, 0));
	m_transform = glm::rotate(m_transform, m_rotation.y, glm::vec3(0, 1, 0));
	m_transform = glm::rotate(m_transform, m_rotation.z, glm::vec3(0, 0, 1));
	m_transform = glm::scale(m_transform, m_scale);
}

std::ostream& operator<<(std::ostream& os, const Effect& effect)
{
	os << "Effect: "
	   << "name: " << effect.m_name << std::endl;
	for (const auto& emitter : effect.m_emitters) {
		os << "	" << *emitter << std::endl;
	}
	return os;
}
