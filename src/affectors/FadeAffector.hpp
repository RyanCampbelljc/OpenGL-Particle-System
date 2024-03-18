#pragma once
#include "BaseAffector.hpp"

// only supports fade out for now
class FadeAffector : public BaseAffector
{
public:
	FadeAffector()
	{
	}
	void apply(Particle* p, float dt) const override;

private:
};