#include "ColorLerpAffector.hpp"
ColorLerpAffector::ColorLerpAffector(const glm::vec3& end)
	: m_end(end)
{
}

void ColorLerpAffector::apply(Particle* p, float dt) const
{
	while (p != nullptr) {
		auto start = p->color.start;
		p->color.value = start + ((m_end - start) * p->scaledLifeTime);
		p = p->next;
	}
}
