#include "cone.hpp"
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

Cone::Cone(): Shape{}, center_{0.0f, 0.0f, 0.0f}, radius_{0.0f}, center2_{0.0f, 0.0f, 0.0f}{}
Cone::Cone(glm::vec3 const& center, float radius, glm::vec3 const& center2): Shape{}, center_{center}, radius_{radius}, center2_{center2}{}
Cone::Cone(std::string name, glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string material) : Shape{name, material}, center_{center}, radius_{radius}, center2_{center2}{}

//Cone::Cone(glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string name, Color const& color):Shape{name, color}, center_{center}, radius_{radius}, center2_{center2}{}
//Cone::~Cone(){std::cout << "Cone Destructor" << std::endl;}

/*Cone::Cone(glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string name, Material const& mat): Shape{name, mat}, center_{center}, radius_{radius}, center2_{center2}{}
Cone::Cone(glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m): Shape{name, name_mat, ka, kd, ks, m}, center_{center}, radius_{radius}, center2_{center2}{}*/



glm::vec3 const& Cone::get_center() const {
	return center_;
}

float const& Cone::get_radius() const {
	return radius_;
}

glm::vec3 const& Cone::get_center2() const {
	return center2_;
	
}

bool Cone::intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const{
	//Gerade durch Mitte des Kegels: p_a + v_a * t, p_a = Stützvektor = center unten, v_a = Richtungsvektor = center oben-center unten
	glm::vec3 p_a = center_;
	glm::vec3 v_a = center2_ - center_;
	
	glm::vec3 p = ray.origin;
	glm::vec3 v = ray.direction;
	
	float a = ;
	float b = ;
	float c = ;
	
	float possibleT[3];
	
	
	float x1;
	float x2;
	
	//unten
	v_a = glm::normalize(v_a);
	glm::vec3 c = glm::normalize(center_);
	glm::vec3 origin = glm::normalize(ray.origin);
	glm::vec3 direction = glm::normalize(ray.direction);
	
	float x3;
	intersectDisk(v_a, c, radius, origin, direction, x3);
}

std::ostream& Cone::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Mittelpunkt Basis: " << center_.x << " " << center_.y << " ";
	os << center_.z << "," << "Radius: " << radius_; << "," << "Spitze: ";
	os << center2_.x << " " << center2_.y << " " << center2_.z;

	return os;
}
