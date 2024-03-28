#include "../samplefw/SampleRunner.h"
#include "../wolf/wolf.h"
#include "Explosion.hpp"
#include "FireSample.hpp"
#include "Reciever.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <stdio.h>

class Week2 : public wolf::App
{
public:
	Week2()
		: wolf::App("Fire System")
	{
		// INIT ALL SAMPLES
		m_sampleRunner.addSample(new FireSample(this));
		m_sampleRunner.addSample(new Explosion(this));
	}

	~Week2()
	{
	}

	void update(float dt) override
	{
		if (isKeyDown(' ')) {
			m_lastDown = true;
		} else if (m_lastDown) {
			m_sampleRunner.nextSample();
			m_lastDown = false;
		}

		if (isKeyJustDown('r')) {
			Reciever::sendSignal(SignalType::ResetEffect, [this](auto reciever) {
				return reciever == dynamic_cast<Reciever*>(m_sampleRunner.getCurrentSample());
			});
		}

		m_sampleRunner.update(dt);
	}

	void render() override
	{
		m_sampleRunner.render(m_width, m_height);
	}

private:
	SampleRunner m_sampleRunner;
	bool m_lastDown = false;
};

int main(int, char**)
{
	Week2 week2;
	week2.run();
}