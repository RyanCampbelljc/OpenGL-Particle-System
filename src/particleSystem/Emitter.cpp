#include "Emitter.hpp"
#include "parser/ConstPropertyNodeReader.hpp"
#include "parser/EmitterFileReader.hpp"
#include "parser/RandomPropertyNodeReader.hpp"

EmitterType EmitterTypeFromString(const std::string& s)
{
	static const std::unordered_map<std::string, EmitterType> emitterTypeTable = {
		{"continuous", EmitterType::continuous}, {"burst", EmitterType::burst}};
	return emitterTypeTable.at(s);
}

// todo may not actually need to store the 1.0f value here
const Emitter::Vertex Emitter::gs_particleVertices[] = {
	// tri 1
	{0.5f, -0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // bottom right
	{-0.5f, 0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top left
	{-0.5f, -0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // bottom left
	// tri 2
	{0.5f, -0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // bottom right
	{0.5f, 0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top right
	{-0.5f, 0.5f, 0.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top left

};

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

	m_pMaterial = wolf::MaterialManager::CreateMaterial("emitter");
	m_pMaterial->SetProgram("shaders/vs.vsh", "shaders/ps.fsh");

	m_pVertexBuffer = wolf::BufferManager::CreateVertexBuffer(
		gs_particleVertices,
		sizeof(Vertex) * (sizeof(gs_particleVertices) / sizeof(gs_particleVertices[0])) * m_numParticles);
	m_pVAO = new wolf::VertexDeclaration();
	m_pVAO->Begin();
	m_pVAO->AppendAttribute(wolf::AT_Position, 4, wolf::CT_Float);
	m_pVAO->AppendAttribute(wolf::AT_Color, 4, wolf::CT_Float);
	m_pVAO->SetVertexBuffer(m_pVertexBuffer);
	m_pVAO->End();

	init();
}

// todo pointers unreadable when this code isnt commented
// i guess something is calling it(copy constructor?)
Emitter::~Emitter()
{
	std::cout << "emitter deconstructor called" << std::endl;
	wolf::MaterialManager::DestroyMaterial(m_pMaterial);
	wolf::BufferManager::DestroyBuffer(m_pVertexBuffer);
	delete m_pVAO;
	delete[] m_pFirstParticle;
	delete[] m_pVerts;
}

// todo add default spawn properties to map if none were in the xml file
void Emitter::init()
{
	Particle* pParticles = new Particle[m_numParticles];
	for (int i = 0; i < m_numParticles; ++i) {
		addToFreePool(&pParticles[i]);
	}
	m_pFirstParticle = pParticles;

	m_pVerts = new Vertex[m_numParticles * sizeof(gs_particleVertices)];
}

// transform is viewProj mat4
void Emitter::render(const glm::mat4& mViewProj, const glm::mat4& transform) const
{
	m_pMaterial->Apply();
	Vertex* pVerts = m_pVerts;
	Particle* pCurrent = m_pActiveList;
	int numVertices = 0;
	while (pCurrent != nullptr) {
		glm::vec3 curPos = pCurrent->pos;
		// note the currPos is the offset of this emitter
		glm::mat4 worldMat = glm::translate(glm::mat4(1.0f), curPos);
		glm::mat4 WVP = mViewProj * worldMat;
		int vertsPerParticle = sizeof(gs_particleVertices) / sizeof(gs_particleVertices[0]);
		for (int i = 0; i < vertsPerParticle; ++i) {
			glm::vec4 v1 =
				WVP * glm::vec4(gs_particleVertices[i].x, gs_particleVertices[i].y, gs_particleVertices[i].z, 1.0f);
			auto color = pCurrent->color;
			pVerts[i].x = v1.x;
			pVerts[i].y = v1.y;
			pVerts[i].z = v1.z;
			pVerts[i].w = v1.w;
			pVerts[i].color.r = color.r;
			pVerts[i].color.g = color.g;
			pVerts[i].color.b = color.b;
			pVerts[i].color.a = color.a;
		}
		pCurrent = pCurrent->next;
		pVerts += vertsPerParticle;
		numVertices += vertsPerParticle;
	}
	m_pVertexBuffer->Write(m_pVerts, sizeof(Vertex) * numVertices);
	m_pVAO->Bind();
	// m_pVAO->Bind();
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void Emitter::update(float dt)
{
	// todo unless == some constant that means infinite life
	if (m_duration < 0.0f) {
		return;
		// todo delete particles;
	}
	m_duration -= dt;
	if (m_type == EmitterType::continuous) {
		m_toSpawnAccumulator += m_spawnRate * dt;
		int numSpawns = (int)(m_toSpawnAccumulator);
		m_toSpawnAccumulator -= numSpawns;
		while (numSpawns--) {
			spawnParticle();
		}
	} else { // random
		;
	}
	// todo update particles in scene
	auto pCurrent = m_pActiveList;
	while (pCurrent != nullptr) {
		pCurrent->pos += (pCurrent->velocity * dt);
		pCurrent = pCurrent->next;
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

Emitter::Particle* Emitter::getFreeParticle()
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

// todo make a local cash of each type so I dont need to use dynamic pointer cast all the time.
void Emitter::spawnParticle()
{
	Particle* p = getFreeParticle();
	p->pos = m_offset;
	auto color = std::dynamic_pointer_cast<ConstPropertyNodeReader>(m_spawnProperties.at("color"));
	if (color) {
		p->color = color->getValue<glm::vec4>();
	} else {
		auto color = std::dynamic_pointer_cast<RandomPropertyNodeReader>(m_spawnProperties.at("color"));
		p->color = Utility::randVec4(color->getMin<glm::vec4>(), color->getMax<glm::vec4>());
	}

	auto velocity = std::dynamic_pointer_cast<ConstPropertyNodeReader>(m_spawnProperties.at("velocity"));
	if (velocity) {
		p->velocity = velocity->getValue<glm::vec3>();
	} else {
		auto velocity = std::dynamic_pointer_cast<RandomPropertyNodeReader>(m_spawnProperties.at("velocity"));
		p->velocity = Utility::randVec3(velocity->getMin<glm::vec3>(), velocity->getMax<glm::vec3>());
	}

	auto size = std::dynamic_pointer_cast<ConstPropertyNodeReader>(m_spawnProperties.at("size"));
	if (size) {
		p->size = size->getValue<float>();
	} else {
		auto size = std::dynamic_pointer_cast<RandomPropertyNodeReader>(m_spawnProperties.at("size"));
		p->size = Utility::randomFloat(size->getMin<float>(), size->getMax<float>());
	}
	// std::cout << p->velocity.x << " " << p->velocity.y << ' ' << p->velocity.z << std::endl;
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