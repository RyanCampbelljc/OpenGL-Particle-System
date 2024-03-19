#pragma once
#include "Utility.hpp"

struct Vertex {
	GLfloat x, y, z, w;
	glm::vec4 color;
	glm::vec2 texCoords;
};

static const Vertex particleVertices[] = {
	// tri 1
	{0.5f, -0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1, 0)}, // bottom right
	{-0.5f, 0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0, 1)}, // top left
	{-0.5f, -0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0, 0)}, // bottom left

	// tri 2
	{0.5f, -0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1, 0)}, // bottom right
	{0.5f, 0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1, 1)}, // top right
	{-0.5f, 0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0, 1)}, // top left

};

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