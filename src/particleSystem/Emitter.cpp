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

const Emitter::Vertex Emitter::gs_particleVertices[] = {
	// tri 1
	{0.5f, -0.5f, 0.5f}, // bottom right
	{-0.5f, 0.5f, 0.5f}, // top left
	{-0.5f, -0.5f, 0.5f}, // bottom left
	// tri 2
	{0.5f, -0.5f, 0.5f}, // bottom right
	{0.5f, 0.5f, 0.5f}, // top right
	{-0.5f, 0.5f, 0.5f}, // top left

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
	m_pVAO->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	m_pVAO->SetVertexBuffer(m_pVertexBuffer);
	m_pVAO->End();

	init();
}

// todo pointers unreadable when this code isnt commented
// i guess something is calling it(copy constructor?)
Emitter::~Emitter()
{
	std::cout << "emitter deconstructor called" << std::endl;
	delete m_pVAO;
	delete[] m_pFirstParticle;
}

void Emitter::init()
{
	Particle* pParticles = new Particle[m_numParticles];
	for (int i = 0; i < m_numParticles; ++i) {
		addToFreePool(&pParticles[i]);
	}
	m_pFirstParticle = pParticles;
}

// transform is viewProj mat4
void Emitter::render(const glm::mat4& mViewProj, const glm::mat4& transform) const
{
	m_pMaterial->Apply();
	Vertex* pVerts = (Vertex*)m_pVertexBuffer;
	Particle* pCurrent = m_pActiveList;
	int count = 0;
	while (pCurrent != nullptr) {
		glm::vec3 curPos = pCurrent->pos;
		// note the currPos is the offset of this emitter
		glm::mat4 worldMat = transform * glm::translate(glm::mat4(1.0f), curPos);
		glm::mat4 WVP = mViewProj * worldMat;
		for (int i = 0; i < 6; ++i) {
			glm::vec4 v1 =
				WVP * glm::vec4(gs_particleVertices[i].x, gs_particleVertices[i].y, gs_particleVertices[i].z, 1.0f);
			pVerts[i].x = v1.x;
			pVerts[i].y = v1.y;
			pVerts[i].z = v1.z;
		}

		pCurrent = pCurrent->next;
		pVerts += 6;
		++count;
	}

	glDrawArrays(GL_TRIANGLES, 0, count);
}

void Emitter::update(float dt)
{
	// todo unless == some constant that means infinite life
	if (m_duration < 0.0f) {
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

void Emitter::spawnParticle()
{
	Particle* p = getFreeParticle();
	p->pos = m_offset;
	addToActivePool(p);
}

void Emitter::particleKilled(Particle* p)
{
	removeFromActive(p);
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
	addToFreePool(p);
}

std::ostream& operator<<(std::ostream& os, const Emitter& emitter)
{
	os << "Emitter: "
	   << "name: " << emitter.getName() << "; num particles: " << emitter.getNumParticles()
	   << "; duration: " << emitter.getDuration() << "; type: " << (int)emitter.getType()
	   << "; spawn rate: " << emitter.getSpawnRate();
	return os;
}