#include "cylinder.hpp"
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

Cylinder::Cylinder(): Shape{}, center_{0.0f, 0.0f, 0.0f}, radius_{0.0f}, height_{0.0f}{}
Cylinder::Cylinder(glm::vec3 const& center, float radius, float height): Shape{}, center_{center}, radius_{radius}, height_{height}{}
Cylinder::Cylinder(std::string name, glm::vec3 const& center, float radius, float height, std::string material) : Shape{name, material}, center_{center}, radius_{radius}, height_{height}{}

//Cylinder::Cylinder(glm::vec3 const& center, float radius, float height, std::string name, Color const& color):Shape{name, color}, center_{center}, radius_{radius}, height_{height}{}
//Cylinder::~Cylinder(){std::cout << "Cylinder Destructor" << std::endl;}

/*Cylinder::Cylinder(glm::vec3 const& center, float radius, float height, std::string name, Material const& mat): Shape{name, mat}, center_{center}, radius_{radius}, height_{height}{}
Cylinder::Cylinder(glm::vec3 const& center, float radius, float height, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m): Shape{name, name_mat, ka, kd, ks, m}, center_{center}, radius_{radius}, height_{height}{}*/



glm::vec3 const& Cylinder::get_center() const {
	return center_;
}

glm::vec3 const& Cylinder::get_radius() const {
	return radius_;
}

glm::vec3 const& Cylinder::get_height() const {
	return height_;
}

/*glm::vec3 const& Cylinder::get_center2() const {
	//Berechnung center des oberen Kreises
}*/


bool Cylinder::intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const{
	/*To intersect a ray with a cylinder with caps:

intersect with the infinite cylinder;

check if the intersection is between the planes;

intersect with each plane;

determine if the intersections are inside caps;

out of all intersections choose the on with minimal t */
}

std::ostream& Cylinder::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Mittelpunkt Basis: " << center_ << "," << "Radius: " << radius_ << "," << "Höhe: " << height_ /*<< "," << "oberer Mittelpunkt: " << get_center2()*/;

	return os;
}
