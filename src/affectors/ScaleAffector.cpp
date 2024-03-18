#include "ScaleAffector.hpp"

ScaleAffector::ScaleAffector(float start, float end)
	: m_start(start)
	, m_end(end)
{
}

void ScaleAffector::apply(Particle* p, float dt) const
{
	while (p != nullptr) {
		p->size = m_start + ((m_end - m_start) * p->scaledLifeTime);
		// float startFade = p->startFade;
		// p->fade = startFade - (p->scaledLifeTime / (1.0f / startFade));
		p = p->next;
	}
}
