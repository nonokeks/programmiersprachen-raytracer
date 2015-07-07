#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"

struct Scene
{
	std::map<Material> material;
	std::vector<Schape> shapes;
	//std::map<LightSource> lights;
	Color ambient;
};


#endif // #ifndef BUW_SHAPE_HPP