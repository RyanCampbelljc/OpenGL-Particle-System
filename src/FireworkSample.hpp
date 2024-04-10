//-----------------------------------------------------------------------------
// File:			FireworkSample.hpp
// Original Author:	Ryan Campbell
/// @brief a sample the renders a firework effect
//-----------------------------------------------------------------------------
#pragma once
#include "../samplefw/Grid3D.h"
#include "../samplefw/Sample.h"
#include "Camera.hpp"
#include "Utility.hpp"
#include "particleSystem/Effect.hpp"

class Firework
	: public Sample
	, public Reciever
{
public:
	//------------------------------------
	// PUBLIC INTERFACE
	//------------------------------------
	Firework(wolf::App* pApp);
	~Firework();

	void init() override;
	void update(float dt) override;
	void render(int width, int height) override;
	void handleSignal(SignalType signal) override;

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
