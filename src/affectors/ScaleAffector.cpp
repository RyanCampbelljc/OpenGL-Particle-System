#include "ScaleAffector.hpp"

void ScaleAffector::apply(Particle* p, float dt) const
{
	while (p != nullptr) {
		auto start = p->scaleStart;
		p->size = start + ((p->scaleEnd - start) * p->scaledLifeTime);
		// float startFade = p->startFade;
		// p->fade = startFade - (p->scaledLifeTime / (1.0f / startFade));
		p = p->next;
	}
}