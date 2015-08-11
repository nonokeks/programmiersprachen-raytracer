#ifndef BUW_OPTIONAL_HIT_HPP
#define BUW_OPTIONAL_HIT_HPP 

#include "shape.hpp"

struct Optional_hit{
	
	Optional_hit() : hit{0}, strahlparam{0.0f}{} 

	bool hit;
	Shape* shape;
	float strahlparam; //Oberflächenpunkt


};

#endif