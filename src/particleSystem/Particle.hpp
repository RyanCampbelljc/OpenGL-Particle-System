#pragma once
#include "Utility.hpp"

// scaledLifeTime 0 when spawn and 1 when over
struct Particle {
	Particle()
		: pos(0.0f, 0.0f, 0.0f)
		, velocity(0.0f, 0.0f, 0.0f)
		, color(0.0f, 0.0f, 0.0f, 0.0f)
		, size(1.0f)
		, fade(1.0f)
		, lifeTime(0.0f)
		, scaledLifeTime(0.0f)
		, next(nullptr)
		, prev(nullptr)
	{
	}

	void updateLifetime(float dt)
	{
		scaledLifeTime += dt / lifeTime;
	}

	void setFade(float f)
	{
		fade = f;
		startFade = fade;
	}
	glm::vec3 pos;
	glm::vec3 velocity;
	glm::vec4 color;
	float size;
	float fade;
	float startFade;
	float lifeTime;
	float scaledLifeTime;
	Particle* next;
	Particle* prev;
};