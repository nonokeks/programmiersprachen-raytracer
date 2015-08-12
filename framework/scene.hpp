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
#include "renderer_data.hpp"
#include <map>
#include <vector>
#include <memory>

struct Scene
{
	Scene(): ambient(), cam(), render(){}
	Scene(Color const& ambient_color, Camera const& camera, Renderer_data const& renderer): ambient(ambient_color), cam(camera), render(renderer){}
	std::map<std::string, Material> material;
	std::vector<std::shared_ptr <Shape>> shapes; 
	std::vector<Light_source> lights;
	Color ambient;
	Camera cam;
	Renderer_data render;

	Scene& operator= (Scene const& rhs){
		material = rhs.material;
		
		for(std::vector<std::shared_ptr <Shape>>::const_iterator it = rhs.shapes.begin(); it != rhs.shapes.end(); ++it){
	 		shapes.push_back(*it);
		}
		for(std::vector<Light_source>::const_iterator it = rhs.lights.begin(); it != rhs.lights.end(); ++it){
			lights.push_back(*it);
		}


		ambient = rhs.ambient;
		cam = rhs.cam;
		render = rhs.render;
		return *this;
	}

	bool operator==(Scene const& rhs){
		if(ambient == rhs.ambient && !cam.get_name().compare(rhs.cam.get_name())
			&& cam.get_angle() == rhs.cam.get_angle() && render.width == rhs.render.width
			&& render.height == rhs.render.height && render.camera_name.compare(rhs.render.camera_name)
			&& render.filename.compare(rhs.render.filename)){
			return true;
		}
		
		
		return false;
	}

};


#endif // #ifndef BUW_SCENE_HPP