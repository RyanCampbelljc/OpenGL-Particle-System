//-----------------------------------------------------------------------------
// File:			Particle.hpp
// Original Author:	Ryan Campbell
/// @brief Various structs and arrays used to represent particles.
//-----------------------------------------------------------------------------
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

/**
 * a better way to organize particle properties that
 * will possibly be interpolated across the particles
 * life time. The affectors hold the end value of the interpolation.
 * Could easily add end values here so they are particle dependant and
 * not affector dependent.
 **/
template<typename T>
struct ParticleProperty {
	T start; // start value of some particle property
	T value; // current value of some particle property.
};

// scaledLifeTime 0 when spawn and 1 when over
struct Particle {
	Particle()
		: pos(0.0f, 0.0f, 0.0f)
		, velocity(0.0f, 0.0f, 0.0f)
		, lifeTime(0.0f)
		, scaledLifeTime(0.0f)
		, next(nullptr)
		, prev(nullptr)
	{
		setStartColor(glm::vec3(0.0f, 0.0f, 0.0f));
		setStartFade(1.0f);
		setStartScale(1.0f);
	}

	void updateLifetime(float dt)
	{
		scaledLifeTime += dt / lifeTime;
	}

	void setStartFade(float f)
	{
		fade.start = f;
		fade.value = f;
	}
	void setStartColor(const glm::vec3& c)
	{
		color.start = c;
		color.value = c;
	}
	void setStartScale(float s)
	{
		scale.start = s;
		scale.value = s;
	}
	glm::vec3 pos;
	glm::vec3 velocity;
	ParticleProperty<glm::vec3> color;
	ParticleProperty<float> scale;
	ParticleProperty<float> fade;
	float lifeTime;
	float scaledLifeTime;
	Particle* next;
	Particle* prev;
};
