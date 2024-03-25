#include "../samplefw/SampleRunner.h"
#include "../wolf/wolf.h"
#include "FireSample.hpp"
#include "FireworkSample.hpp"
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
		m_sampleRunner.addSample(new FireworkSample(this));
	}

	~Week2()
	{
	}

	void update(float dt) override
	{
		if (isKeyDown(' ')) {
			m_lastDown = true;
		} else if (m_lastDown) {
			// IF YOU WANT TO SWITCH SAMPLES
			m_sampleRunner.nextSample();
			m_lastDown = false;
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