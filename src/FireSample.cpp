
//-----------------------------------------------------------------------------
// File:			FireSample.cpp
// Original Author:	Ryan Campbell
/// @brief a sample the renders a fire
//-----------------------------------------------------------------------------
#include "FireSample.hpp"
#include "../samplefw/Grid2D.h"
#include <iostream>

FireSample::FireSample(wolf::App* pApp)
	: Sample(pApp, "FireSample")
	, Reciever()
	, m_grid(1)
	, m_cam(1280, 720, pApp)
	, m_fireEffect(Utility::EFFECT_FIRE)
{
}

FireSample::~FireSample()
{
}

void FireSample::init()
{
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	m_fireEffect.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_fireEffect.setscale(glm::vec3(3.0f, 3.0f, 3.0f));
	// rotation looks a little weird but works
	// m_fireEffect.setrotation(glm::vec3(0.0f, 0.0f, 0.0f));
	std::cout << m_fireEffect;
}

void FireSample::update(float dt)
{
	m_cam.update(dt);
	m_fireEffect.update(dt);
}

void FireSample::render(int width, int height)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_grid.render(m_cam.getView(), m_cam.getProjection());
	m_fireEffect.render(m_cam.getCamParams());
}

void FireSample::handleSignal(SignalType signal)
{
	switch (signal) {
		case SignalType::ResetEffect:
			m_fireEffect.resetEffect();
			break;

		default:
			throw std::exception("invalid signalType");
	}
}