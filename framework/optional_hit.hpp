#ifndef BUW_OPTIONAL_HIT_HPP
#define BUW_OPTIONAL_HIT_HPP 

#include <glm/vec3.hpp>
#include <memory>
#include <ray.hpp>

#include "shape.hpp"

struct Optional_hit{
	
	Optional_hit():
		hit{0},
		distance{0.0f}, 
		intersection{0.0f, 0.0f, 0.0f},
		normal{0.0f, 0.0f, 0.0f}{} 

	bool hit;
	Shape* shape; 
	float distance;
	glm::vec3 intersection;
	glm::vec3 normal;
	

	Optional_hit& operator=(const Optional_hit& rhs){
		if(this==&rhs){ //Operator ist nicht implementiert..? MUSS DER JETZT NOCH IMPLEMENTIERT WERDEN ODER IST DAS EGAL?
			return *this;
		}
		hit = rhs.hit;
		distance = rhs.distance;
		intersection = rhs.intersection;
		normal = rhs.normal;
		shape = rhs.shape;
		return *this;
	}
	
};

#endif