#ifndef BUW_SDF_LOADER_HPP
#define BUW_SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <glm/vec3.hpp>
#include <map>
#include <sstream>  
#include <string>

#include "box.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "cone.hpp"
#include "cylinder.hpp"
#include "light_source.hpp"
#include "material.hpp"
#include "renderer_data.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

using namespace std;

class Sdf_loader {
	public:
		Sdf_loader(std::string file);
		Sdf_loader();
		~Sdf_loader();

		Scene load_scene(std::string file) const;
		
		//void load_material(std::string file, std::map<std::string, Material>& material);
		std::string get_file() const;

	private:
		std::string file_;
};

#endif // #ifndef BUW_SDF_LOADER_HPP