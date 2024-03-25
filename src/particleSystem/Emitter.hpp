#pragma once
#include "Camera.hpp"
#include "Utility.hpp"
#include "affectors/VelocityAffector.hpp"
#include "parser/PropertyNodeWrapper.hpp"
#include "particleSystem/Particle.hpp"
#include <unordered_map>
enum class EmitterType { continuous, burst };
EmitterType EmitterTypeFromString(const std::string& s);

class Emitter
{
public:
	Emitter(std::string file, glm::vec3 offset);

	// Emitter(Emitter&) = delete;
	~Emitter();
	void init();

	void render(const Camera::CamParams& params, const glm::mat4& transform) const;
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
	void resetEmitter();
	// todo should this be inside the class?
	// compile error when removing friend keyword?
	friend std::ostream& operator<<(std::ostream& os, const Emitter&);

private:
	void addToFreePool(Particle* p);
	void addToActivePool(Particle* p);
	Particle* getFreeParticle();
	void spawnParticle();
	void particleKilled(Particle* p);
	void removeFromActive(Particle* p);

private:
	glm::vec3 m_offset;
	std::string m_name;
	int m_numParticles;
	float m_duration;
	EmitterType m_type;
	int m_spawnRate;
	float m_toSpawnAccumulator;
	Particle* m_pFreeList;
	Particle* m_pActiveList;
	Particle* m_pActiveTail;
	// ref to first particle in mem. Used to delete later.
	Particle* m_pFirstParticle;
	std::unordered_map<std::string, std::shared_ptr<PropertyNodeWrapper>> m_spawnProperties;
	wolf::VertexBuffer* m_pVertexBuffer;
	wolf::VertexDeclaration* m_pVAO;
	wolf::Material* m_pMaterial;
	std::vector<std::shared_ptr<BaseAffector>> m_affectors;
	// used as a buffer to store vertex data before writing to the actual buffer
	Vertex* m_pVerts;
	wolf::Texture* m_pTexture;

	// vars to reset when reset signal occurs
	float m_lifetime;
	bool m_runBurstOnce;
};
