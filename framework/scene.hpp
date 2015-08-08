#ifndef BUW_Scene_HPP
#define BUW_Scene_HPP
#include <iostream>
#include <string>
#include "color.hpp"
#include "shape.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "light_source.hpp"
#include "renderer.hpp"
#include <map>
#include <vector>

struct Scene
{
	Scene(): ambient(), cam(), render(0.0, 0.0, ""){};
	Scene(Color const& ambient_color, Camera const& camera, Renderer const& renderer): ambient(ambient_color), cam(camera), render(renderer){};
	std::map<std::string, Material> material;
	std::vector<Shape> shapes; // shared pointer
	std::vector<Light_source> lights;
	Color ambient;
	Camera cam;
	Renderer render;

};


#endif // #ifndef BUW_SCENE_HPP