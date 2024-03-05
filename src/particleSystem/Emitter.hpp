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
	struct Vertex {
		GLfloat x, y, z;
	};
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

	Emitter(std::string file, glm::vec3 offset);
	// Emitter(Emitter&) = delete;
	~Emitter();
	void init();

	void render(const glm::mat4& mViewProj, const glm::mat4& transform) const;
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
	void addToFreePool(Particle* p);
	void addToActivePool(Particle* p);
	Particle* getFreeParticle();
	void spawnParticle();
	void particleKilled(Particle* p);
	void removeFromActive(Particle* p);

private:
	// EMITTER PROPERTIES
	glm::vec3 m_offset;
	std::string m_name;
	int m_numParticles;
	float m_duration;
	EmitterType m_type;
	int m_spawnRate;
	float m_toSpawnAccumulator;
	Particle* m_pFreeList; // add things to the head of the free list
	Particle* m_pActiveList;
	Particle* m_pActiveTail;
	Particle* m_pFirstParticle;
	std::unordered_map<std::string, std::shared_ptr<PropertyNodeReader>> m_spawnProperties;
	static const Vertex gs_particleVertices[];
	wolf::VertexBuffer* m_pVertexBuffer;
	wolf::VertexDeclaration* m_pVAO;
	wolf::Material* m_pMaterial;
	// still need affectorList();
};

std::ostream& operator<<(std::ostream& os, const Emitter&);

/**
 * PLAN
 * be able to add spawn properties to particles and have them spawn
 * make sure all different combos work ie continuous, burst, overlife etc
 *
 * After that working fine then worry about adding list of affectors to the emitter class
 */