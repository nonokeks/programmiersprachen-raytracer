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

Cylinder::Cylinder(): Shape{}, center_{0.0f, 0.0f, 0.0f}, radius_{0.0f}, center2_{0.0f, 0.0f, 0.0f}{}
Cylinder::Cylinder(glm::vec3 const& center, float radius, glm::vec3 const& center2): Shape{}, center_{center}, radius_{radius}, center2_{center2}{}
Cylinder::Cylinder(std::string name, glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string material) : Shape{name, material}, center_{center}, radius_{radius}, center2_{center2}{}

//Cylinder::Cylinder(glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string name, Color const& color):Shape{name, color}, center_{center}, radius_{radius}, center2_{center2}{}
//Cylinder::~Cylinder(){std::cout << "Cylinder Destructor" << std::endl;}

/*Cylinder::Cylinder(glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string name, Material const& mat): Shape{name, mat}, center_{center}, radius_{radius}, center2_{center2}{}
Cylinder::Cylinder(glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m): Shape{name, name_mat, ka, kd, ks, m}, center_{center}, radius_{radius}, center2_{center2}{}*/



glm::vec3 const& Cylinder::get_center() const {
	return center_;
}

float const& Cylinder::get_radius() const {
	return radius_;
}

glm::vec3 const& Cylinder::get_center2() const {
	return center2_;
}


bool Cylinder::intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const{
	//To intersect a ray with a cylinder with caps:
	
	//-intersect with the infinite cylinder;
	//Gerade durch Mitte des Zylinders: p_a + v_a * t, p_a = Stützvektor = center unten, v_a = Richtungsvektor = center oben-center unten
	glm::vec3 p_a = center_;
	glm::vec3 v_a = center2_ - center_;
	
	glm::vec3 p = ray.origin;
	glm::vec3 v = ray.direction;
	
	float a = (v-((glm::dot(v,v_a))*v_a))*(v-((glm::dot(v,v_a))*v_a));
	float b = 2*((v-(glm::dot(v,v_a))*(glm::dot(v_a,(p-p_a))))-((glm::dot((p-p_a),v_a))*v_a));
	float c = ((p-p_a)-(glm::dot((p-p_a),v_a))*v_a)* ((p-p_a)-(glm::dot((p-p_a),v_a))*v_a)- (radius*radius);
	
	float possibleT[4];
	
	float x1;
	float x2;
	
	solveQuadratic(a, b, c, x1, x2);
	
	//-check if the intersection is between the planes;
	
	glm::vec3 q1 = p + v*x1
	if (x1 > 0 && (glm::dot(v_a, (q1 - center_))) > 0){ //ist && das richtige?? beides muss true sein
		possibleT[0] = x1;
	}
	
	glm::vec3 q2 = p + v*x2
	if (x2 > 0 && (glm::dot(v_a, (q2 - center2_))) > 0){
		possibleT[1] = x2;
	}

	//-intersect with each plane;
	
	v_a = glm::normalize(v_a);
	v_a2 = glm::normalize(center_ - center2_)
	glm::vec3 c = glm::normalize(center_);
	glm::vec3 c2 = glm::normalize(center2_);
	glm::vec3 origin = glm::normalize(ray.origin);
	glm::vec3 direction = glm::normalize(ray.direction);
	
	float x3;
	float x4;
	
	intersectDisk(v_a, c, radius, origin, direction, x3);
	intersectDisk(v_a2, c2, radius, origin, direction, x4);
	
	//-determine if the intersections are inside caps;  wird eigentlich schon in intersectdisk geprüft, soll man x3/x4 einfach so in possible t setzen?
	glm::vec3 q3 = p + v*x3
	if (x3 > 0 && (((q3 - center_)*(q3 - center_)) < r*r)){ 
		possibleT[2] = x3;
	}
	
	glm::vec3 q4 = p + v*x4
	if (x4 > 0 && (((q4 - center2_)*(q4 - center2_)) < r*r)){
		possibleT[3] = x4;
	}

	//-out of all intersections choose the on with minimal t
	// geht bestimmt kürzer
	float t = possibleT[0];
	for (int i = 1; i < 4; i++){
		if (t == 0 && possibleT[i] > 0){
			t = possibleT[i]
		}
		else if(possibleT[i] < t && possibleT[i] > 0){
			t = possibleT[i]
		}
	}
	
	if (t > 0){
		intersection = p + v*t;
		
		if(t == x1 || t == x2){
			glm::vec3 b = intersection - p_a;
			float r = (glm::dot(b, v_a))/glm::length(v_a);
			glm::vec3 f = p_a + (r/glm::length(v_a))*v_a;
			normal = intersection - f;
		}		
		
		else if(t == x3){
		normal = v_a;
		}	
		
		else if(t == x1){
		normal = v_a2;
		}	
		
		return true;
	}
	
	else {
		return false;

	}
}

std::ostream& Cylinder::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Mittelpunkt Basis: " << center_.x << " " << center_.y << " ";
	os << center_.z << "," << "Radius: " << radius_ << "," << "oberer Mittelpunkt: ";
	os << center2_.x << " " << center2_.y << " " << center2_.z;

	return os;
}
