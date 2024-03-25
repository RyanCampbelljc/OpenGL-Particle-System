#pragma once
#include "../samplefw/Grid3D.h"
#include "../samplefw/Sample.h"
#include "Camera.hpp"
#include "Utility.hpp"
#include "particleSystem/Effect.hpp"

class FireworkSample : public Sample
{
public:
	//------------------------------------
	// PUBLIC INTERFACE
	//------------------------------------
	FireworkSample(wolf::App* pApp);
	~FireworkSample();

	void init() override;
	void update(float dt) override;
	void render(int width, int height) override;
	//------------------------------------

private:
	//------------------------------------
	// PRIVATE MEMBERS
	//------------------------------------
	Grid3D m_grid;
	Camera m_cam;
	Effect m_fireworkEffect;
	//------------------------------------
};
