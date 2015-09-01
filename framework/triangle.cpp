#include "triangle.hpp"

#define _USE_MATH_DEFINES

/* im header
#include <cmath>
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>*/

//warum hier wenn es im header auskommentiert ist?
#include "material.hpp"

Triangle::Triangle():
	Shape{},
	a_{0.0f, 0.0f, 0.0f},
	b_{0.0f, 0.0f, 0.0f},
	c_{0.0f, 0.0f, 0.0f}{}
	
Triangle::Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c):
	Shape{},
	a_{a},
	b_{b},
	c_{c}{}
	
Triangle::Triangle(std::string name, glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, std::string material):
	Shape{name, material},
	a_{a},
	b_{b},
	c_{c}{}

//delete?
//Triangle::Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, std::string name, Color const& color):Shape{name, color}, a_{a}, b_{b}, c_{c}{}
//Triangle::~Triangle(){std::cout << "Triangle Destructor" << std::endl;}
/*Triangle::Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, std::string name, Material const& mat): Shape{name, mat}, a_{a}, b_{b}, c_{c}{}
Triangle::Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, 
float m): Shape{name, name_mat, ka, kd, ks, m}, a_{a}, b_{b}, c_{c}{}*/

glm::vec3 const& Triangle::get_a() const {
	return a_;
}

glm::vec3 const& Triangle::get_b() const {
	return b_;
}

glm::vec3 const& Triangle::get_c() const {
	return c_;
}

bool Triangle::intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const{
	normal = glm::normalize(glm::cross(a_ - b_, a_ - c_)); //Cross = Kreuzprodukt
	if(glm::dot(normal, ray.direction) > 0) {
		normal *= -1;
	}
	
	glm::vec3 direct = glm::normalize(ray.direction);
	distance = (glm::dot(a_,normal) - glm::dot(normal,ray.origin)) / glm::dot(direct, normal);
	return glm::intersectLineTriangle(ray.origin, direct, a_, b_, c_, intersection);
}

//delete?
/*
bool Triangle::intersect(Ray const& ray, float& distance) const{
	glm::vec3 normal = glm::normalize(glm::cross(a_ - b_, a_ - c_)); //Cross = Kreuzprodukt
	if(glm::dot(normal, ray.direction) > 0) {
		normal *= -1;
	}
	glm::vec3 intersection;
	
	glm::vec3 direct = glm::normalize(ray.direction);
	distance = (glm::dot(a_,normal) - glm::dot(normal,ray.origin)) / glm::dot(direct, normal);
	return glm::intersectLineTriangle(ray.origin, direct, a_, b_, c_, intersection);
}*/

std::ostream& Triangle::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Point A: " << a_.x << " " << a_.y << " " << a_.z << ",";
	os << "Point B: " << b_.x << " " << b_.y << " " << b_.z << ",";
	os << "Point C: " << c_.x << " " << c_.y << " " << c_.z;

	return os;
}
