#pragma once
#include "../wolf/wolf.h"
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <pugixml.hpp>
#include <string>
#include <time.h>
#include <unordered_map>
#include <vector>
// https://github.com/zeux/pugixml
namespace Utility
{
constexpr const char* const EFFECT_FIRE = "assets/fire.effect";
float randomFloat(float min, float max);
int randomInt(int min, int max);
glm::vec3 randVec3(glm::vec3 min, glm::vec3 max);
glm::vec4 randVec4(glm::vec4 min, glm::vec4 max);
}; // namespace Utility