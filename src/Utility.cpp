//-----------------------------------------------------------------------------
// File:			Utility.cpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#include "Utility.hpp"
namespace Utility
{
// random seed for random function
static void initSeed()
{
	static bool once = true;
	if (once) {
		srand((unsigned int)time(NULL));
		once = false;
	}
}

// returns random in inclusive
int randomInt(int min, int max)
{
	initSeed();
	if (max < min) {
		return min;
	}
	return (rand() % (max - min + 1)) + min;
}

// returns random float inclusive
float randomInRange(float min, float max)
{
	initSeed();
	if (max < min) {
		auto temp = max;
		max = min;
		min = temp;
	}
	float somePercentage = (float)rand() / (float)RAND_MAX;
	return min + (somePercentage * (max - min));
}

glm::vec3 randomInRange(glm::vec3 min, glm::vec3 max)
{
	initSeed();
	return glm::vec3(randomInRange(min.x, max.x), randomInRange(min.y, max.y), randomInRange(min.z, max.z));
}

glm::vec4 randomInRange(glm::vec4 min, glm::vec4 max)
{
	initSeed();
	return glm::vec4(
		randomInRange(min.x, max.x), randomInRange(min.y, max.y), randomInRange(min.z, max.z),
		randomInRange(min.w, max.w));
}
} // namespace Utility