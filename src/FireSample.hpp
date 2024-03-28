//-----------------------------------------------------------------------------
// File:			FireSample.hpp
// Original Author:	Ryan Campbell
/// @brief a sample the renders a fire
//-----------------------------------------------------------------------------
#pragma once
#include "../samplefw/Grid3D.h"
#include "../samplefw/Sample.h"
#include "Camera.hpp"
#include "Utility.hpp"
#include "particleSystem/Effect.hpp"

class FireSample
	: public Sample
	, public Reciever
{
public:
	//------------------------------------
	// PUBLIC INTERFACE
	//------------------------------------
	FireSample(wolf::App* pApp);
	~FireSample();

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
	Effect m_fireEffect;
	//------------------------------------
};
