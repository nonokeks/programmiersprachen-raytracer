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
#define PI 3.14159265

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
	
	float height = glm::length(v_a);
	float beta = atan(height/radius) * PI/180; //Winkel an der Fläche
	float alpha = PI/2 - beta; //Winkel an der Spitze = zwischen Gerade und einer Seite
	
	float a = cos(alpha) * cos(alpha) * (v - glm::dot(v, v_a) * v_a) * (v - glm::dot(v, v_a) * v_a) - sin(alpha) * sin(alpha) * (glm::dot(v, v_a)) * (glm::dot(v, v_a));
	float b = 2 * cos(alpha) * cos(alpha) * (v - glm::dot(v, v_a) * (glm::dot(v_a,(p-p_a))) - (glm::dot((p-p_a), v_a)) * v_a) - 2 * sin(alpha) * sin(alpha) * glm::dot(v, v_a) * glm::dot((p-p_a), v_a);
	float c = cos(alpha) * cos(alpha) * ((p-p_a) - glm::dot((p-p_a), v_a) * v_a) * ((p-p_a) - glm::dot((p-p_a), v_a) * v_a) - sin(alpha) * sin(alpha) * glm::dot((p-p_a), v_a) * glm::dot((p-p_a), v_a);
	
	float possibleT[3];
	
	float x1;
	float x2;
	
	solveQuadratic(a, b, c, x1, x2);
	
	//schauen ob die intersection zwischen Spitze und Basis ist
	glm::vec3 q1 = p + v*x1
	if (//Bedingung?? gleiche wie bei cylinder?){
		possibleT[0] = x1;
	}
	
	glm::vec3 q2 = p + v*x2
	if (){
		possibleT[1] = x2;
	}
	
	//unten
	v_a = glm::normalize(v_a);
	glm::vec3 c = glm::normalize(center_);
	glm::vec3 origin = glm::normalize(ray.origin);
	glm::vec3 direction = glm::normalize(ray.direction);
	
	float x3;
	intersectDisk(v_a, c, radius, origin, direction, x3);
	possibleT[2] = x3;
	
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
			//??
		}		
		
		else if(t == x3){
		normal = v_a;
		}	

		return true;
	}
	
	else {
		return false;

	}
}

std::ostream& Cone::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Mittelpunkt Basis: " << center_.x << " " << center_.y << " ";
	os << center_.z << "," << "Radius: " << radius_; << "," << "Spitze: ";
	os << center2_.x << " " << center2_.y << " " << center2_.z;

	return os;
}
