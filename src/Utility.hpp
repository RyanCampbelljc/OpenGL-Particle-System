//-----------------------------------------------------------------------------
// File:			Utility.hpp
// Original Author:	Ryan Campbell
/// @brief Common functions and includes.
//-----------------------------------------------------------------------------
#pragma once
#include "../wolf/wolf.h"
#include <algorithm>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <pugixml.hpp>
#include <random>
#include <string>
#include <time.h>
#include <unordered_map>
#include <vector>
// https://github.com/zeux/pugixml
namespace Utility
{
constexpr const char* const EFFECT_FIRE = "assets/fire.effect";
constexpr const char* const EFFECT_EXPLOSION = "assets/explosion.effect";
int randomInt(int min, int max);

// Allows you to call randomInRange on any type.
// if the type is float,vec3,or vec4 one of the specific implementations below is called.
// needed in RandomPropertyNodeReader.getValue()
template<typename T>
T randomInRange(T min, T max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<T> dis(min, max);
	return dis(gen);
}
float randomInRange(float min, float max);
glm::vec3 randomInRange(glm::vec3 min, glm::vec3 max);
glm::vec4 randomInRange(glm::vec4 min, glm::vec4 max);
}; // namespace Utility