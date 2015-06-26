#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/vec3.hpp>

struct Ray
{
	Ray(glm::vec3 const& o, glm::vec3 const& d):origin{o}, direction{d}{}
	glm::vec3 origin;
	glm::vec3 direction;
};

#endif //#define BUW_RAY_HPP