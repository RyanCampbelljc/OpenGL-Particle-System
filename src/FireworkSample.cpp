//-----------------------------------------------------------------------------
// File:			FireworkSample.cpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#include "FireworkSample.hpp"

Firework::Firework(wolf::App* pApp)
	: Sample(pApp, "FireworkSample")
	, Reciever()
	, m_grid(1)
	, m_cam(1280, 720, pApp)
	, m_fireworkEffect(Utility::EFFECT_FIREWORK)
{
}

Firework::~Firework()
{
}

void Firework::init()
{
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	m_fireworkEffect.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_fireworkEffect.setscale(glm::vec3(3.0f, 3.0f, 3.0f));
	std::cout << m_fireworkEffect;
}

void Firework::update(float dt)
{
	m_cam.update(dt);
	m_fireworkEffect.update(dt);
}

void Firework::render(int width, int height)
{
	glClearColor(120 / 255.0f, 150 / 255.0f, 185 / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_grid.render(m_cam.getView(), m_cam.getProjection());
	m_fireworkEffect.render(m_cam.getCamParams());
}

void Firework::handleSignal(SignalType signal)
{
	switch (signal) {
		case SignalType::ResetEffect:
			m_fireworkEffect.resetEffect();
			break;

		default:
			throw std::exception("invalid signalType");
	}
}