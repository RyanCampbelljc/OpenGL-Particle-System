#pragma once
#include "Utility.hpp"
#include "particleSystem/Particle.hpp"
// #include "particleSystem/Emitter.hpp"

class BaseAffector
{
public:
	BaseAffector()
	{
	}
	virtual void apply(Particle* p, float dt) const = 0;

private:
};