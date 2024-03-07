#pragma once
#include "BaseAffector.hpp"
class VelocityAffector : public BaseAffector
{
public:
	VelocityAffector()
	{
	}
	void apply(Particle* p, float dt) const override;

private:
};