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

// returns random float inclusive
float randomFloat(float min, float max)
{
	initSeed();
	if (max < min) {
		return min;
		puts("max was less than min in utility::randomFloat()");
	}
	float somePercentage = (float)rand() / (float)RAND_MAX;
	return min + (somePercentage * (max - min));
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

glm::vec3 randVec3(glm::vec3 first, glm::vec3 second)
{
	initSeed();
	float maxX, maxY, maxZ, minX, minY, minZ, x, y, z;
	if (first.x > second.x) {
		maxX = first.x;
		minX = second.x;
	} else {
		maxX = second.x;
		minX = first.x;
	}

	if (first.y > second.y) {
		maxY = first.y;
		minY = second.y;
	} else {
		maxY = second.y;
		minY = first.y;
	}

	if (first.z > second.z) {
		maxZ = first.z;
		minZ = second.z;
	} else {
		maxZ = second.z;
		minZ = first.z;
	}
	return glm::vec3(randomFloat(minX, maxX), randomFloat(minY, maxY), randomFloat(minZ, maxZ));
}
} // namespace Utility