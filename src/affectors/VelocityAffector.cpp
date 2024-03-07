#include "affectors/VelocityAffector.hpp"
void VelocityAffector::apply(Particle* p, float dt) const
{
	while (p != nullptr) {
		p->pos += p->velocity * dt;
		p = p->next;
	}
}
