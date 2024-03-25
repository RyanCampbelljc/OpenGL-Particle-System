#include "FireworkSample.hpp"

FireworkSample::FireworkSample(wolf::App* pApp)
	: Sample(pApp, "FireworkSample")
	, m_grid(1)
	, m_cam(1280, 720, pApp)
	, m_fireworkEffect(Utility::EFFECT_FIREWORK)
{
}

FireworkSample::~FireworkSample()
{
}

void FireworkSample::init()
{
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	m_fireworkEffect.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_fireworkEffect.setscale(glm::vec3(3.0f, 3.0f, 3.0f));
	// rotation looks a little weird but works
	// m_fireEffect.setrotation(glm::vec3(0.0f, 0.0f, 0.0f));
	std::cout << m_fireworkEffect;
}

void FireworkSample::update(float dt)
{
	if (m_pApp->isKeyJustDown('r')) {
		m_fireworkEffect.resetEffect();
	}
	m_cam.update(dt);
	m_fireworkEffect.update(dt);
}

void FireworkSample::render(int width, int height)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_grid.render(m_cam.getView(), m_cam.getProjection());
	m_fireworkEffect.render(m_cam.getCamParams());
}