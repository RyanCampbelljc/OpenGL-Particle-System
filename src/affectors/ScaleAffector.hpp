#pragma once
#include "BaseAffector.hpp"
class ScaleAffector : public BaseAffector
{
public:
	ScaleAffector()
	{
	}
	void apply(Particle* p, float dt) const override;

private:
};