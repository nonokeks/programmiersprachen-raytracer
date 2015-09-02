#ifndef BUW_Scene_HPP
#define BUW_Scene_HPP

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "camera.hpp"
#include "color.hpp"
#include "composite.hpp"
#include "light_source.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "renderer_data.hpp"
#include "shape.hpp"

struct Scene{
	Scene():
		ambient(),
		cam(),
		render(){}
		
	Scene(Color const& ambient_color, Camera const& camera, 
		  Renderer_data const& renderer):
		ambient(ambient_color),
		cam(camera),
		render(renderer){}
		
	std::map<std::string, Material> material;
	std::vector<std::shared_ptr <Composite>> shape_composite; 
	//std::vector<std::shared_ptr <Shape>> shapes; 
	std::vector<Light_source> lights;
	Color ambient;
	Camera cam;
	Renderer_data render;

	Scene& operator= (Scene const& rhs){
		material.clear();
		shape_composite.clear();
		lights.clear();

		material.insert(rhs.material.begin(), rhs.material.end());
		shape_composite.insert(shape_composite.begin(), 
					rhs.shape_composite.begin(), rhs.shape_composite.end());
		lights.insert(lights.begin(), rhs.lights.begin(), rhs.lights.end());

		ambient = rhs.ambient;
		cam = rhs.cam;
		render = rhs.render;
		return *this;
	}

	bool operator==(Scene const& rhs){
		if(ambient == rhs.ambient && 
			!cam.get_name().compare(rhs.cam.get_name()) && cam.get_angle()
			== rhs.cam.get_angle() && render.width == rhs.render.width 
			&& render.height == rhs.render.height 
			&& render.camera_name.compare(rhs.render.camera_name)
			&& render.filename.compare(rhs.render.filename)){
			return true;
		}
		return false;
	}
};

#endif // #ifndef BUW_SCENE_HPP