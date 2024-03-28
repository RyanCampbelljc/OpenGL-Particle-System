//-----------------------------------------------------------------------------
// File:			AccelerationAffector.hpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#pragma once
#include "BaseAffector.hpp"

class AccelerationAffector : public BaseAffector
{
public:
	AccelerationAffector(const glm::vec3& end);
	void apply(Particle* p, float dt) const override;

private:
	// amount to change velocity by per second.
	glm::vec3 m_velocityChange;
};