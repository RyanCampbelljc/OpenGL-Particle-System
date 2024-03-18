#pragma once
#include "Camera.hpp"
#include "Emitter.hpp"
#include "Utility.hpp"
class Effect
{
public:
	Effect(std::string file);
	void play();
	void stop();
	void pause();
	void seek(float time);
	void setTransform(const glm::mat4& transform);
	void update(float dt);
	void render(const Camera::CamParams& params) const;
	void toString() const;

private:
	glm::mat4 m_transform;
	std::string m_name;
	std::vector<Emitter*> m_emitters;
	bool m_playing;
	float m_dt;
};