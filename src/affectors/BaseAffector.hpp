//-----------------------------------------------------------------------------
// File:			BaseAffector.hpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#pragma once
#include "Utility.hpp"
#include "particleSystem/Particle.hpp"

class BaseAffector
{
public:
	BaseAffector()
	{
	}
	virtual void apply(Particle* p, float dt) const = 0;

private:
};