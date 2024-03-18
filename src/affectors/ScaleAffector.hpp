#pragma once
#include "BaseAffector.hpp"
class ScaleAffector : public BaseAffector
{
public:
	ScaleAffector(float start, float end);
	void apply(Particle* p, float dt) const override;
	float m_start;
	float m_end;

private:
};