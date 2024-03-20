#include "affectors/FadeAffector.hpp"

FadeAffector::FadeAffector(float end)
	: m_end(end)
{
}

// todo fix edge case of divide by 0 here
void FadeAffector::apply(Particle* p, float dt) const
{
	// This formula just allows the fade to be faded over life time
	// but not having to start at a fade value of 1. It will start at whatever value
	// is given to it in the spawn properties.
	while (p != nullptr) {
		float startFade = p->fade.start;
		p->fade.value = startFade + ((m_end - startFade) * p->scaledLifeTime);
		p = p->next;
	}
}
