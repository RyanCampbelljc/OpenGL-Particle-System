#include "Emitter.hpp"
#include "affectors/FadeAffector.hpp"
#include "affectors/ScaleAffector.hpp"
#include "parser/ConstPropertyNodeReader.hpp"
#include "parser/EmitterFileReader.hpp"
#include "parser/RandomPropertyNodeReader.hpp"
EmitterType EmitterTypeFromString(const std::string& s)
{
	static const std::unordered_map<std::string, EmitterType> emitterTypeTable = {
		{"continuous", EmitterType::continuous}, {"burst", EmitterType::burst}};
	return emitterTypeTable.at(s);
}

Emitter::Emitter(std::string file, glm::vec3 offset)
	: m_offset(offset)
	, m_toSpawnAccumulator(0.0f)
	, m_pFreeList(nullptr)
	, m_pActiveList(nullptr)
	, m_pActiveTail(nullptr)
{
	EmitterFileReader scan(file);
	m_name = scan.getName();
	m_numParticles = scan.getNumParticles();
	m_duration = scan.getDuration();
	m_type = scan.getType();
	m_spawnRate = scan.getSpawnRate();
	m_spawnProperties = scan.getSpawnProperties();
	m_affectors = scan.getAffectors();

	m_pMaterial = wolf::MaterialManager::CreateMaterial(m_name);
	m_pMaterial->SetProgram("assets/shaders/vs.vsh", "assets/shaders/ps.fsh");

	// todo make this settable via xml
	m_pMaterial->SetBlend(true);
	m_pMaterial->SetBlendEquation(wolf::BE_Add);

	// converts string specifying blend mode to an int that corresponds to
	//  the proper value in the wolf::blendMode enum
	// todo unhard code the order of these
	// todo make it work if only 2 are specified
	auto blendModes = scan.getBlendModes();
	auto srcRGB = wolf::stringToBlendMode.at(blendModes[0]);
	auto dstRGB = wolf::stringToBlendMode.at(blendModes[1]);
	auto srcAlpha = wolf::stringToBlendMode.at(blendModes[2]);
	auto dstAlpha = wolf::stringToBlendMode.at(blendModes[3]);
	m_pMaterial->SetBlendMode(
		wolf::BlendMode(srcRGB), wolf::BlendMode(dstRGB), wolf::BlendMode(srcAlpha), wolf::BlendMode(dstAlpha));
	// use this equation for smoke
	// if (m_name == "smoke") {
	// 	m_pMaterial->SetBlendMode(wolf::BM_SrcAlpha, wolf::BM_OneMinusSrcAlpha, wolf::BM_One, wolf::BM_One);
	// } else if (m_name == "flame") {
	// 	m_pMaterial->SetBlendMode(wolf::BM_SrcAlpha, wolf::BM_DstAlpha, wolf::BM_One, wolf::BM_One);
	// } else if (m_name == "sparks") {
	// 	m_pMaterial->SetBlendMode(wolf::BM_SrcAlpha, wolf::BM_OneMinusSrcAlpha);
	// }

	m_pTexture = wolf::TextureManager::CreateTexture(scan.getTexturePath().c_str());
	m_pMaterial->SetTexture("u_texture1", m_pTexture);
	m_pVertexBuffer = wolf::BufferManager::CreateVertexBuffer(sizeof(Vertex) * 6 * m_numParticles, GL_DYNAMIC_DRAW);
	m_pVAO = new wolf::VertexDeclaration();
	m_pVAO->Begin();
	m_pVAO->AppendAttribute(wolf::AT_Position, 4, wolf::CT_Float);
	m_pVAO->AppendAttribute(wolf::AT_Color, 4, wolf::CT_Float);
	m_pVAO->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	m_pVAO->SetVertexBuffer(m_pVertexBuffer);
	m_pVAO->End();

	init();
}

Emitter::~Emitter()
{
	std::cout << "emitter deconstructor called" << std::endl;
	wolf::MaterialManager::DestroyMaterial(m_pMaterial);
	wolf::BufferManager::DestroyBuffer(m_pVertexBuffer);
	delete m_pVAO;
	delete[] m_pFirstParticle;
	delete[] m_pVerts;
}

void Emitter::init()
{
	// create particles and add to free pool
	Particle* pParticles = new Particle[m_numParticles];
	for (int i = 0; i < m_numParticles; ++i) {
		addToFreePool(&pParticles[i]);
	}
	// a pointer to the first particle in memory that will never change that can be used later to free memory
	m_pFirstParticle = pParticles;

	// creating a buffer that can hold vertex data that can be passed to vertexBuffer.write();
	m_pVerts = new Vertex[m_numParticles * sizeof(particleVertices)];
}

// transform is viewProj mat4
void Emitter::render(const Camera::CamParams& params, const glm::mat4& transform) const
{
	Vertex* pVerts = m_pVerts;
	Particle* pCurrent = m_pActiveList;
	int numVertices = 0;
	while (pCurrent != nullptr) {
		glm::mat4 worldMat = glm::translate(glm::mat4(1.0f), pCurrent->pos);
		glm::mat3 view = params.view;
		glm::mat4 bboard = glm::transpose(view);
		worldMat = worldMat * bboard;
		auto scale = pCurrent->scale.value;
		worldMat = glm::scale(worldMat, glm::vec3(scale, scale, scale));
		// worldMat = bboard * worldMat; this one feels weird
		glm::mat4 WVP = params.proj * params.view * worldMat;
		int vertsPerParticle = sizeof(particleVertices) / sizeof(particleVertices[0]);
		for (int i = 0; i < vertsPerParticle; ++i) {
			glm::vec4 v1 =
				WVP
				* glm::vec4(particleVertices[i].x, particleVertices[i].y, particleVertices[i].z, particleVertices[i].w);
			auto color = pCurrent->color.value;
			pVerts[i].x = v1.x;
			pVerts[i].y = v1.y;
			pVerts[i].z = v1.z;
			pVerts[i].w = v1.w;
			pVerts[i].color.r = color.r;
			pVerts[i].color.g = color.g;
			pVerts[i].color.b = color.b;
			pVerts[i].color.a = pCurrent->fade.value;
			pVerts[i].texCoords.x = particleVertices[i].texCoords.x;
			pVerts[i].texCoords.y = particleVertices[i].texCoords.y;
		}
		pCurrent = pCurrent->next;
		pVerts += vertsPerParticle;
		numVertices += vertsPerParticle;
	}
	m_pVertexBuffer->Write(m_pVerts, sizeof(Vertex) * numVertices);
	m_pMaterial->Apply();
	m_pVAO->Bind();
	// todo just sort items instead
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void Emitter::update(float dt)
{
	static float lifeTime = 0.0f;
	lifeTime += dt;

	if (lifeTime <= m_duration || m_duration == -1) {
		if (m_type == EmitterType::continuous) {
			m_toSpawnAccumulator += m_spawnRate * dt;
			int numSpawns = (int)(m_toSpawnAccumulator);
			m_toSpawnAccumulator -= numSpawns;
			while (numSpawns--) {
				spawnParticle();
			}
		}
	} else { // lifetime over emmit burst
		static bool runOnce = true;
		if (m_type == EmitterType::burst && runOnce) {
			while (m_numParticles--) {
				spawnParticle();
			}
		}
		runOnce = false;
	}

	// update particle life time
	Particle* pCurrent = m_pActiveList;
	while (pCurrent != nullptr) {
		pCurrent->updateLifetime(dt);
		// put this here and not at end to account for particle possibly being killed
		auto next = pCurrent->next;
		if (pCurrent->scaledLifeTime >= 1) {
			particleKilled(pCurrent);
		}
		pCurrent = next;
	}

	// apply affectors to active list
	for (const auto& affector : m_affectors) {
		affector->apply(m_pActiveList, dt);
	}
}

// pushes to front of free pool
void Emitter::addToFreePool(Particle* p)
{
	p->prev = nullptr;
	p->next = m_pFreeList;
	if (m_pFreeList != nullptr)
		m_pFreeList->prev = p;
	m_pFreeList = p;
}

void Emitter::addToActivePool(Particle* p)
{
	p->prev = nullptr;
	p->next = m_pActiveList;
	if (m_pActiveList != nullptr)
		m_pActiveList->prev = p;
	else { // active list was null
		m_pActiveTail = p;
	}
	m_pActiveList = p;
}

Particle* Emitter::getFreeParticle()
{
	Particle* pReturn;
	if (m_pFreeList != nullptr) { // make sure free list isnt empty
		pReturn = m_pFreeList;
		m_pFreeList = m_pFreeList->next;
		if (m_pFreeList != nullptr) // make sure its not empty again(could have just been 1 elem in list)
			m_pFreeList->prev = nullptr;
		else {
		}
		pReturn->prev = nullptr;
		pReturn->next = nullptr;
		return pReturn;
	} else { // free list empty;
		pReturn = m_pActiveTail;
		removeFromActive(pReturn);
	}
	return pReturn;
}

void Emitter::spawnParticle()
{
	Particle* p = getFreeParticle();
	// todo make spawn pos point or rand within a radius
	p->pos = (m_offset + Utility::randVec3(glm::vec3(-0.1f, 0, -0.1f), glm::vec3(0.1f, 0, 0.1f)));

	if (m_spawnProperties.count("color") > 0) {
		auto color = std::dynamic_pointer_cast<ConstPropertyNodeReader>(m_spawnProperties.at("color"));
		if (color) {
			p->setStartColor(color->getValue<glm::vec3>());
		} else {
			auto color = std::dynamic_pointer_cast<RandomPropertyNodeReader>(m_spawnProperties.at("color"));
			p->setStartColor(Utility::randVec3(color->getMin<glm::vec3>(), color->getMax<glm::vec3>()));
		}
	}

	if (m_spawnProperties.count("velocity") > 0) {
		auto velocity = std::dynamic_pointer_cast<ConstPropertyNodeReader>(m_spawnProperties.at("velocity"));
		if (velocity) {
			p->velocity = velocity->getValue<glm::vec3>();
		} else {
			auto velocity = std::dynamic_pointer_cast<RandomPropertyNodeReader>(m_spawnProperties.at("velocity"));
			p->velocity = Utility::randVec3(velocity->getMin<glm::vec3>(), velocity->getMax<glm::vec3>());
		}
	}

	if (m_spawnProperties.count("size") > 0) {
		auto size = std::dynamic_pointer_cast<ConstPropertyNodeReader>(m_spawnProperties.at("size"));
		if (size) {
			p->setStartScale(size->getValue<float>());
		} else {
			auto size = std::dynamic_pointer_cast<RandomPropertyNodeReader>(m_spawnProperties.at("size"));
			p->setStartScale(Utility::randomFloat(size->getMin<float>(), size->getMax<float>()));
		}
	}

	if (m_spawnProperties.count("lifetime") > 0) {
		auto lifetime = std::dynamic_pointer_cast<ConstPropertyNodeReader>(m_spawnProperties.at("lifetime"));
		if (lifetime) {
			p->lifeTime = lifetime->getValue<float>();
		} else {
			auto lifetime = std::dynamic_pointer_cast<RandomPropertyNodeReader>(m_spawnProperties.at("lifetime"));
			p->lifeTime = Utility::randomFloat(lifetime->getMin<float>(), lifetime->getMax<float>());
		}
	}

	if (m_spawnProperties.count("fade") > 0) {
		auto fade = std::dynamic_pointer_cast<ConstPropertyNodeReader>(m_spawnProperties.at("fade"));
		if (fade) {
			p->setStartFade(fade->getValue<float>());
		} else {
			auto fade = std::dynamic_pointer_cast<RandomPropertyNodeReader>(m_spawnProperties.at("fade"));
			p->setStartFade(Utility::randomFloat(fade->getMin<float>(), fade->getMax<float>()));
		}
	}

	p->scaledLifeTime = 0.0f;
	addToActivePool(p);
}

void Emitter::particleKilled(Particle* p)
{
	removeFromActive(p);
	addToFreePool(p);
}

void Emitter::removeFromActive(Particle* p)
{
	// currently could be anywhere in active list
	if (p == m_pActiveList) {
		// removing from front of list
		if (p->next == nullptr) {
			m_pActiveList = nullptr;
			m_pActiveTail = nullptr;
		} else {
			m_pActiveList = p->next;
		}
	} else if (p == m_pActiveTail) { // end of list
		m_pActiveTail = p->prev;
		m_pActiveTail->next = nullptr;
	} else if (p->next != nullptr) { // middle of list
		p->next->prev = p->prev;
		p->prev->next = p->next;
	} else {
		throw std::exception("list messed");
	}
}

std::ostream& operator<<(std::ostream& os, const Emitter& emitter)
{
	os << "Emitter: "
	   << "name: " << emitter.getName() << "; num particles: " << emitter.getNumParticles()
	   << "; duration: " << emitter.getDuration() << "; type: " << (int)emitter.getType()
	   << "; spawn rate: " << emitter.getSpawnRate();
	return os;
}