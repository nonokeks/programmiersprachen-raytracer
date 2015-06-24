#include "box.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include "color.hpp"

Box::Box() :min_{0.0f, 0.0f, 0.0f}, max_{0.0f, 0.0f, 0.0f} {}
Box::Box(glm::vec3 min, glm::vec3 max):Shape{}, min_{min}, max_{max} {}
Box::Box(glm::vec3 min, glm::vec3 max, std::string name, Color color):Shape{name, color}, min_{min}, max_{max} {}


glm::vec3 Box::get_min()const{
	return min_;
}
glm::vec3 Box::get_max()const{
	return max_;
}

float Box::area() const{
	float depth = fabs(max_.x - min_.x);
	float width = fabs(max_.y - min_.y);
	float high = fabs(max_.z - min_.z);
	return (2 * high * width + 2 * width * depth + 2 * high * depth) ;
}
float Box::volume() const{
	float depth = fabs(max_.x - min_.x);
	float width = fabs(max_.y - min_.y);
	float high = fabs(max_.z - min_.z);
	return (high * width * depth);
}