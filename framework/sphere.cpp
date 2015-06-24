#include "sphere.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include "color.hpp"

Sphere::Sphere(): center_{0.0f, 0.0f, 0.0f}, radius_{0.0}{}
Sphere::Sphere(glm::vec3 const& center, float radius): Shape{}, center_{center}, radius_{radius} {}
Sphere::Sphere(glm::vec3 const& center, float radius, std::string name, Color color):Shape{name, color}, center_{center}, 
radius_{radius}{}


glm::vec3 const& Sphere::get_center() const {
	return center_;
}

float Sphere::get_radius() const{
	return radius_;
}


float Sphere::area() const{
	return (4 * M_PI * radius_ * radius_);
}
float Sphere::volume() const{
	float temp = (4 * M_PI * pow(radius_,3))/3;
	return temp;
}