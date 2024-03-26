
#include "FireSample.hpp"
#include "../samplefw/Grid2D.h"
#include "imgui.h"
// #include "imgui_impl_glfw.cpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
// todo prob a better spot to put this imgui stuff // prob in things that switched between samples
FireSample::FireSample(wolf::App* pApp)
	: Sample(pApp, "FireSample")
	, m_grid(1)
	, m_cam(1280, 720, pApp)
	, m_fireEffect(Utility::EFFECT_FIRE)
{
	// todo get this  working
	//  	// Setup Dear ImGui context
	//  	IMGUI_CHECKVERSION();
	//  	ImGui::CreateContext();
	//  	ImGuiIO& io = ImGui::GetIO();
	//  	(void)io;
	//  	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	//  	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

	// 	// Setup Dear ImGui style
	// 	ImGui::StyleColorsDark();
	// 	// ImGui::StyleColorsLight();

	// 	// Setup Platform/Renderer backends
	// 	ImGui_ImplGlfw_InitForOpenGL(pApp->getWindow(), true);
	// #ifdef __EMSCRIPTEN__
	// 	ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
	// #endif
	// 	ImGui_ImplOpenGL3_Init("#version 150"); // ? proper version?
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