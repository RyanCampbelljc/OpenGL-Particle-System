
#include "FireSample.hpp"
#include "../samplefw/Grid2D.h"

#include <iostream>

FireSample::FireSample(wolf::App* pApp)
	: Sample(pApp, "FireSample")
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
	glDisable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	//  glEnable(GL_MULTISAMPLE);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_fireEffect.setTransform(transform);
	m_fireEffect.toString();
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
	m_fireEffect.render(m_cam.getProjection() * m_cam.getView());
}