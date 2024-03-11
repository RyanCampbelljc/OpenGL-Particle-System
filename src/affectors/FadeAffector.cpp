#include "affectors/FadeAffector.hpp"
void FadeAffector::apply(Particle* p, float dt) const
{
	// This formula just allows the fade to be faded over life time
	// but not having to start at a fade value of 1. It will start at whatever value
	// is given to it in the spawn properties.
	while (p != nullptr) {
		float startFade = p->startFade;
		p->fade = startFade - (p->scaledLifeTime / (1.0f / startFade));
		p = p->next;
	}
}
