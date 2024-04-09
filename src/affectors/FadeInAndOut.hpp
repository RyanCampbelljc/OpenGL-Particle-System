//-----------------------------------------------------------------------------
// File:			FadeInAndOut.hpp
// Original Author:	Ryan Campbell
// Fades to the end value 1/2 way through its life then fades from m_end to 0 from 1/2 lfe to end
//-----------------------------------------------------------------------------
#pragma once
#include "BaseAffector.hpp"

class FadeInAndOut : public BaseAffector
{
public:
	FadeInAndOut(float end);
	void apply(Particle* p, float dt) const override;

private:
	float m_end;
};