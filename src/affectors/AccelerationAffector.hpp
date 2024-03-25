#pragma once
#include "BaseAffector.hpp"

// only supports fade out for now
class AccelerationAffector : public BaseAffector
{
public:
	AccelerationAffector(const glm::vec3& end);
	void apply(Particle* p, float dt) const override;

private:
	glm::vec3 m_velocityChange;
};