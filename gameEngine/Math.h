#pragma once

#include <glm\glm.hpp>

namespace gE
{
	extern float barycentricInterpolation(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, glm::vec2& pos);
}