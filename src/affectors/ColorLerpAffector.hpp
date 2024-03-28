//-----------------------------------------------------------------------------
// File:			ColorLerpAffector.hpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#pragma once
#include "BaseAffector.hpp"

class ColorLerpAffector : public BaseAffector
{
public:
	ColorLerpAffector(const glm::vec3& end);
	void apply(Particle* p, float dt) const override;

private:
	// the particles color at the end of its liftime
	glm::vec3 m_end;
};