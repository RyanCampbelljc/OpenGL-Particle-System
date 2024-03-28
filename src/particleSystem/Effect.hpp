//-----------------------------------------------------------------------------
// File:			Effect.hpp
// Original Author:	Ryan Campbell
/// @brief Emitter container.
// Inherits from reciver interface so it can recieve signal such as resetEmiiter()
//-----------------------------------------------------------------------------
#pragma once
#include "Camera.hpp"
#include "Emitter.hpp"
#include "Reciever.hpp"
#include "Utility.hpp"

class Effect
{
public:
	Effect(std::string file);
	// these arnt actually implemented yes
	void play();
	void stop();
	void pause();
	void seek(float time);
	//
	void setPosition(const glm::vec3& pos);
	void setscale(const glm::vec3& scale);
	void setrotation(const glm::vec3& rot);
	void update(float dt);
	void render(const Camera::CamParams& params) const;
	friend std::ostream& operator<<(std::ostream& os, const Effect&);
	void resetEffect();

private:
	void updateTransfrom();
	glm::mat4 m_transform;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	std::string m_name;
	std::vector<std::shared_ptr<Emitter>> m_emitters;
	bool m_playing;
	float m_dt;
};