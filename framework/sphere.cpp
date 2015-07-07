#include "sphere.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

Sphere::Sphere(): Shape{}, center_{0.0f, 0.0f, 0.0f}, radius_{0.0}{}
Sphere::Sphere(glm::vec3 const& center, float radius): Shape{}, center_{center}, radius_{radius} {}
//Sphere::Sphere(glm::vec3 const& center, float radius, std::string name, Color const& color):Shape{name, color}, center_{center}, 
//radius_{radius}{}
//Sphere::~Sphere(){std::cout << "Sphere Destructor" << std::endl;}

Sphere::Sphere(glm::vec3 const& center, float radius, std::string name, Material const& mat) : Shape{name, mat}, center_{center}, radius_{radius} {}
Sphere::Sphere(glm::vec3 const& center, float radius, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, 
float m):Shape{name, name_mat, ka, kd, ks, m}, center_{center}, radius_{radius} {}


glm::vec3 const& Sphere::get_center() const {
	return center_;
}

float Sphere::get_radius() const{
	return radius_;
}

bool Sphere::intersect(Ray const& ray, float& distance)const{
	glm::vec3 direct = glm::normalize(ray.direction);
	return glm::intersectRaySphere(ray.origin, direct, center_, radius_*radius_, distance);
}


float Sphere::area() const{
	return (4 * M_PI * radius_ * radius_);
}

float Sphere::volume() const{
	float temp = (4 * M_PI * pow(radius_,3))/3;
	return temp;
}

std::ostream& Sphere::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Radius: " << radius_ << ", Center: " << center_.x << " " << center_.y << " " << center_.z;

	return os;
}