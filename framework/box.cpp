#include "box.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include "color.hpp"

Box::Box() : Shape{}, min_{0.0f, 0.0f, 0.0f}, max_{0.0f, 0.0f, 0.0f} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max):Shape{}, min_{min}, max_{max} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color const& color):Shape{name, color}, min_{min}, max_{max} {}
//Box::~Box(){std::cout << "Box Destructor" << std::endl;}

//Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Material const& mat):Shape{name, mat}, min_{min}, max_{max} {}
//Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks,
// float m):Shape{name, name_mat, ka, kd, ks, m}, min_{min}, max_{max} {}


glm::vec3 const& Box::get_min()const{
	return min_;
}
glm::vec3 const& Box::get_max()const{
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

std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Min: " << min_.x << " " << min_.y << " " << min_.z << ", Max: "<< max_.x << " " << max_.y << " " << max_.z;
	return os;
}