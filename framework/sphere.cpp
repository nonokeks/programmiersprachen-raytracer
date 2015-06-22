#include "sphere.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

Sphere::Sphere(): center_{0.0f, 0.0f, 0.0f}, radius_{0.0}{}
Sphere::Sphere(glm::vec3 const& center, float radius): center_{center}, radius_{radius}{}
Sphere::~Sphere(){}

glm::vec3 const& Sphere::get_center() const {
	return center_;
}

float Sphere::get_radius() const{
	return radius_;
}


float Sphere::area() const{
	return (4 * M_PI * pow(radius_,2));
}
float Sphere::volume() const{
	return (4/3 * M_PI * pow(radius_,3));
}