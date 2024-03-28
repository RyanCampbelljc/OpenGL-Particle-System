//-----------------------------------------------------------------------------
// File:			AccelerationAffector.cpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#include "AccelerationAffector.hpp"
AccelerationAffector::AccelerationAffector(const glm::vec3& velocityChange)
	: m_velocityChange(velocityChange)
{
}

void AccelerationAffector::apply(Particle* p, float dt) const
{
	while (p != nullptr) {
		p->velocity += m_velocityChange * dt;
		p = p->next;
	}
}
