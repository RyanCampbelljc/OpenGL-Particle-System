//-----------------------------------------------------------------------------
// File:			FadeAffector.hpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#pragma once
#include "BaseAffector.hpp"

class FadeAffector : public BaseAffector
{
public:
	FadeAffector(float end);
	// supports fading in an out as this function
	// lerps from particle->fade.start to m_end
	void apply(Particle* p, float dt) const override;

private:
	float m_end;
};