//-----------------------------------------------------------------------------
// File:			ScaleAffector.hpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#pragma once
#include "BaseAffector.hpp"
class ScaleAffector : public BaseAffector
{
public:
	ScaleAffector(float end);
	// supports scaling in an out as this function
	// lerps from particle->scale.start to m_end
	void apply(Particle* p, float dt) const override;

private:
	float m_end;
};