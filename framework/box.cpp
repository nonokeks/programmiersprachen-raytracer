#include "box.hpp"

Box::Box() :min_{0.0f, 0.0f, 0.0f}, max_{0.0f, 0.0f, 0.0f} {}
Box::Box(glm::vec3 min, glm::vec3 max): min_{min}, max_{max} {}
Box::~Box();

glm::vec3 Box::get_min()const{
	return min_;
}
glm::vec3 Box::get_max()const{
	return max_;
}

float Box::area() const{
	return 0;
}
float Box::volume() const{
	return 0;
}