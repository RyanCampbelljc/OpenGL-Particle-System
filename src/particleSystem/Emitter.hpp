#pragma once
// #include "ParticleProperties.hpp"
#include "Utility.hpp"
#include "parser/PropertyNodeReader.hpp"
#include "unordered_map"

enum class EmitterType { continuous, burst };
EmitterType EmitterTypeFromString(const std::string& s);

class Emitter
{
public:
	// template<typename T>
	// struct SpawnProperty {
	// 	std::string name;
	// 	bool isRandom;
	// 	T min;
	// 	T max;
	// 	T value;
	// 	T getValue()
	// 	{
	// 		if (isRandom) {
	// 			// return in random range
	// 		}
	// 		return value;
	// 	}
	// };
	struct Particle {
		glm::vec3 pos;
		glm::vec3 velocity;
		glm::vec4 color;
		float size;
		float fade;
		float lifeTime;
		Particle* next;
		Particle* prev;
	};

	Emitter(std::string file, glm::vec3 offset);
	void init();

	void render(glm::mat4 transform) const;
	void update(float dt);
	std::string getName() const
	{
		return m_name;
	}
	int getNumParticles() const
	{
		return m_numParticles;
	}

	float getDuration() const
	{
		return m_duration;
	}
	int getSpawnRate() const
	{
		return m_spawnRate;
	}
	EmitterType getType() const
	{
		return m_type;
	}

private:
	void addToPool(Particle* p);
	Particle* getFreeParticle();
	void spawnParticle();
	void particleKilled(Particle* p);

private:
	// EMITTER PROPERTIES
	glm::vec3 m_offset;
	std::string m_name;
	int m_numParticles;
	float m_duration;
	EmitterType m_type;
	int m_spawnRate;
	// todo array?
	std::vector<Particle*> m_freeList;
	std::vector<Particle*> m_activeList;
	std::unordered_map<std::string, std::shared_ptr<PropertyNodeReader>> m_spawnProperties;
	// still need affectorList();
	// list of particles
	// vbo/ vao/ material for each emitter
};

std::ostream& operator<<(std::ostream& os, const Emitter&);

/**
 * PLAN
 * be able to add spawn properties to particles and have them spawn
 * make sure all different combos work ie continuous, burst, overlife etc
 *
 * After that working fine then worry about adding list of affectors to the emitter class
 */