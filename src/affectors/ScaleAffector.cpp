#include "ScaleAffector.hpp"

ScaleAffector::ScaleAffector(float end)
	: m_end(end)
{
}

void ScaleAffector::apply(Particle* p, float dt) const
{
	while (p != nullptr) {
		auto start = p->scale.start;
		p->scale.value = start + ((m_end - start) * p->scaledLifeTime);
		p = p->next;
	}
}
