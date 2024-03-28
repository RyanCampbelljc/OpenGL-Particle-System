//-----------------------------------------------------------------------------
// File:			Explosion.cpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#include "Explosion.hpp"

Explosion::Explosion(wolf::App* pApp)
	: Sample(pApp, "ExplosionSample")
	, Reciever()
	, m_grid(1)
	, m_cam(1280, 720, pApp)
	, m_explosionEffect(Utility::EFFECT_EXPLOSION)
{
}

Explosion::~Explosion()
{
}

void Explosion::init()
{
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	m_explosionEffect.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_explosionEffect.setscale(glm::vec3(3.0f, 3.0f, 3.0f));
	// rotation looks a little weird but works
	// m_fireEffect.setrotation(glm::vec3(0.0f, 0.0f, 0.0f));
	std::cout << m_explosionEffect;
}

void Explosion::update(float dt)
{
	m_cam.update(dt);
	m_explosionEffect.update(dt);
}

void Explosion::render(int width, int height)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_grid.render(m_cam.getView(), m_cam.getProjection());
	m_explosionEffect.render(m_cam.getCamParams());
}

void Explosion::handleSignal(SignalType signal)
{
	switch (signal) {
		case SignalType::ResetEffect:
			m_explosionEffect.resetEffect();
			break;

		default:
			throw std::exception("invalid signalType");
	}
}