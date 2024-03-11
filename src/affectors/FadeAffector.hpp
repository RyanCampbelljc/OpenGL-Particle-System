#pragma once
#include "BaseAffector.hpp"
class FadeAffector : public BaseAffector
{
public:
	FadeAffector()
	{
	}
	void apply(Particle* p, float dt) const override;

private:
};