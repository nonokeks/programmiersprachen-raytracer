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

Cone::Cone(): Shape{}, center_{0.0f, 0.0f, 0.0f}, radius_{0.0f}, height_{0.0f}{}
Cone::Cone(glm::vec3 const& center, float radius, float height): Shape{}, center_{center}, radius_{radius}, height_{height}{}
Cone::Cone(std::string name, glm::vec3 const& center, float radius, float height, std::string material) : Shape{name, material}, center_{center}, radius_{radius}, height_{height}{}

//Cone::Cone(glm::vec3 const& center, float radius, float height, std::string name, Color const& color):Shape{name, color}, center_{center}, radius_{radius}, height_{height}{}
//Cone::~Cone(){std::cout << "Cone Destructor" << std::endl;}

/*Cone::Cone(glm::vec3 const& center, float radius, float height, std::string name, Material const& mat): Shape{name, mat}, center_{center}, radius_{radius}, height_{height}{}
Cone::Cone(glm::vec3 const& center, float radius, float height, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m): Shape{name, name_mat, ka, kd, ks, m}, center_{center}, radius_{radius}, height_{height}{}*/



glm::vec3 const& Cone::get_center() const {
	return center_;
}

glm::vec3 const& Cone::get_radius() const {
	return radius_;
}

glm::vec3 const& Cone::get_height() const {
	return height_;
}

/*glm::vec3 const& Cone::get_center2() const {
	//Berechnung Spitze
	
}*/

bool Cone::intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const{
	//wohin rayplane, raydisc?
	//raydisc für unterseite
	//rest?
}

std::ostream& Cone::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Mittelpunkt: " << center_ << "," << "Radius: " << radius_ << "," << "Höhe: " << height_ /*<< "," << "Spitze: " << get_center2()*/;

	return os;
}
