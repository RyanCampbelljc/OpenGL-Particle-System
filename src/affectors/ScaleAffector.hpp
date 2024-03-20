#pragma once
#include "BaseAffector.hpp"
class ScaleAffector : public BaseAffector
{
public:
	ScaleAffector(float end);
	void apply(Particle* p, float dt) const override;

private:
	float m_end;
};