#pragma once
#include <string>
#include <vector>

class Sample;

class SampleRunner
{
public:
	SampleRunner();
	~SampleRunner();

	void update(float dt);
	void render(int width, int height);

	void addSample(Sample* pSample);
	void switchToSampleNumber(int num);
	void switchToSampleWithName(const std::string& name);
	void nextSample();
	Sample* getCurrentSample();

private:
	void _sampleChanged();
	Sample* m_pCurrSample;
	std::vector<Sample*> m_samples;
	int m_currSampleNumber;
};