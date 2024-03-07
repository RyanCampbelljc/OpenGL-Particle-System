#pragma once
#include "Utility.hpp"
struct Particle {
	Particle()
		: pos(0.0f, 0.0f, 0.0f)
		, velocity(0.0f, 0.0f, 0.0f)
		, color(0.0f, 0.0f, 0.0f, 0.0f)
		, size(1.0f)
		, fade(-1.0f)
		, lifeTime(9999)
		, next(nullptr)
		, prev(nullptr)
	{
	}
	glm::vec3 pos;
	glm::vec3 velocity;
	glm::vec4 color;
	float size;
	float fade;
	float lifeTime;
	Particle* next;
	Particle* prev;
};