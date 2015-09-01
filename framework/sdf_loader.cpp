/*#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  
#include <glm/vec3.hpp>
#include "scene.hpp"
#include "material.hpp"
#include <map>
#include "camera.hpp"
#include "light_source.hpp"
#include "color.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "renderer_data.hpp"
#include "triangle.hpp"
#include "cone.hpp"
#include "cylinder.hpp"
*/

#include "sdf_loader.hpp"

using namespace std;

Sdf_loader::Sdf_loader(std::string file):
	file_{file}{}
	
Sdf_loader::Sdf_loader():
	file_{""} {}
	
Sdf_loader::~Sdf_loader(){}

Scene Sdf_loader::load_scene(std::string file) const{
//delete?
	//file_ = file; // noetig?

	ifstream datei(file, ios::in);
 	Scene s{};
 	std::string line;
 	std::string word = " ";
 	std::string name = " ";
 	std::stringstream sstr; // for string to float
 	// shapes container
 	std::map<std::string, std::shared_ptr<Shape>> shape_map;

 	if (datei.good()){
		while(datei >> word){
 			if (word.compare("#") == 0){ // ignore comments
	 			datei >> word; // read next word = ignore this line
				//DELETE?
	 			//Komplette Zeile automatisch?

	 			/*
	 			if(word.compare("camera") == 0 ||
				   word.compare("render") == 0 || word.compare("define") == 0){
	 			    
	 			    //datei >> word;
	 			}*/
	 			
	 		}
			
			// Camera
	 		else if (word.compare("camera") == 0){ 
	 			datei >> name;
	 			datei >> word;
				sstr << word; //String to Float
				float angle;
				sstr >> angle;
				sstr.clear();

				datei >> word;
			
				if (word.compare("#") != 0 && word.compare("render") != 0 && 
				   word.compare("camera") != 0 && word.compare("define") != 0){

					float x, y, z;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word;
		 			sstr >> x >> y >> z;
		 			glm::vec3 position(x,y,z);
		 			sstr.clear(); // Clear stringstream

		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word;
		 			sstr >> x >> y >> z;
		 			glm::vec3 direction(x,y,z);
		 			sstr.clear(); // Clear stringstream

		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word;
		 			sstr >> x >> y >> z;
		 			glm::vec3 up(x,y,z);
		 			sstr.clear(); // Clear stringstream

		 			Camera c{name, angle, position, direction, up};
		 			s.cam = c;
				}
				else{
					Camera c{name, angle};
					s.cam = c;
				}
	 		}
			
			//Renderer
	 		else if (word.compare("render") == 0){
	 			datei >> name; //Kamera Name ..? //HAT DAS NOCH BEDEUTUNG?
	 			std::string filename;
	 			datei >> filename;

	 			unsigned x_res;
	 			unsigned y_res;
	 			datei >> word;
	 			sstr << word << ' ';
	 			datei >> word;
	 			sstr << word;
	 			sstr >> x_res >> y_res;
	 			sstr.clear();

	 			Renderer_data render{x_res, y_res, name, filename};
	 			s.render = render;
	 		}
			
			// Class definitions
	 		else if (word.compare("define") == 0){ 
	 			datei >> word;
				
	 			if (word.compare("material") == 0){// Materials for Shapes
		 			float r,g,b;
		 			datei >> name;
		 			//only if material name is unique
		 			if(s.material.find(name) == s.material.end()){
		 				//ka
		 				sstr.clear();
			 			datei >> word;
			 			sstr << word << ' ';
			 			datei >> word;
			 			sstr << word << ' ';
			 			datei >> word;
			 			sstr << word;
			 			sstr >> r >> g >> b;
			 			Color ka(r,g,b);
			 			sstr.clear();
			 			
			 			//kd
			 			datei >> word;
			 			sstr << word << ' ';
			 			datei >> word;
			 			sstr << word << ' ';
			 			datei >> word;
			 			sstr << word;
			 			sstr >> r >> g >> b;
			 			Color kd(r,g,b);
			 			sstr.clear();

			 			//ks
			 			datei >> word;
			 			sstr << word << ' ';
			 			datei >> word;
			 			sstr << word << ' ';
			 			datei >> word;
			 			sstr << word;
			 			sstr >> r >> g >> b;
			 			Color ks(r,g,b);
			 			sstr.clear();

			 			float m, re, o;
			 			datei >> word;
			 			sstr << word << ' ';
			 			datei >> word;
			 			sstr << word << ' ';
			 			datei >> word;
			 			sstr << word;
			 			sstr >> m >> re >> o;
			 			sstr.clear();

			 			Material mat{name, ka, kd, ks, m, re, o};
					    s.material[name] = mat;
		 			}
		 		}
				
				// Light sources
		 		else if (word.compare("light") == 0){
		 			datei >> name;

		 			//Position
		 			float x, y, z;
		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word;
		 			sstr >> x >> y >> z;
		 			glm::vec3 position(x,y,z);
		 			sstr.clear(); // Clear stringstream
					
					//La
					float r, g, b;
					datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word;
		 			sstr >> r >> g >> b;
		 			Color la(r,g,b);
		 			sstr.clear(); //Clear stringstream

		 			//Ld
					datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word << ' ';
		 			datei >> word;
		 			sstr << word;
		 			sstr >> r >> g >> b;
		 			Color ld(r,g,b);
		 			sstr.clear(); 

		 			Light_source light(name, position, la, ld);
		 			s.lights.push_back(light);

		 		}
				
				//Shapes
	 			else if (word.compare("shape") == 0){
	 				datei >> word;
					
					//Box
	 				if (word.compare("box") == 0){
			 			datei >> name;
			 			if(shape_map.find(name) == shape_map.end()){
				 			float x,y,z;
							
				 			//min
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 min(x,y,z);
				 			sstr.clear();

				 			//max
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 max(x,y,z);
				 			sstr.clear();
				 			
				 			datei >> word; // Material name

				 			std::shared_ptr<Shape> b(new Box(name, min, max, word));
				 			//KANN DAS WEG?
							//s.shapes.push_back(b);

				 			//Box b(name, min, max, word);
				 			shape_map[name] = b;
			 			}
			 		}
					
					// Sphere
			 		else if (word.compare("sphere") == 0){
			 			datei >> name;
						
			 			if(shape_map.find(name) == shape_map.end()){
						
				 			float x,y,z;
				 			//center
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 center(x,y,z);

				 			sstr.clear();

				 			float r;
				 			//radius
				 			datei >> word;
				 			sstr << word;
				 			sstr >> r;
				 			sstr.clear();

				 			datei >> word; // Material name

				 			std::shared_ptr<Shape> sph(new Sphere(name, center, r, word));
							
							//WEG?
				 			//s.shapes.push_back(sph);
				 			//Sphere sph(name, center, r, word);
				 			shape_map[name] = sph;
				 		}
		 			}
					
					//Triangle
		 			else if (word.compare("triangle") == 0){
			 			datei >> name;
			 			float x,y,z;
						
			 			if(shape_map.find(name) == shape_map.end()){
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 a(x,y,z);
				 			sstr.clear();

				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 b(x,y,z);
				 			sstr.clear();

				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 c(x,y,z);
				 			sstr.clear();
				 			
				 			datei >> word; // Material name

				 			std::shared_ptr<Shape> tri(new Triangle(name, a, b, c, word));
							//WEG?
				 			//s.shapes.push_back(tri);
				 			//Triangle tri(name, a, b, c, word);
				 			shape_map[name] = tri;
				 		}
		 			}
					
					//Cone
		 			else if (word.compare("cone") == 0){
			 			datei >> name;
						
			 			if(shape_map.find(name) == shape_map.end()){
				 			float x,y,z,r;
				 			
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 center1(x,y,z);
				 			sstr.clear();

				 			datei >> word;
				 			sstr << word;
				 			sstr >> r;
				 			sstr.clear();

				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 center2(x,y,z);
				 			sstr.clear();
				 			
				 			datei >> word; // Material name

				 			std::shared_ptr<Shape> cone(new Cone(name, center1, r, center2, word));
							//WEG??
				 			//s.shapes.push_back(cone);
				 			//Cone co(name, center1, r, center2, word);
				 			shape_map[name] = cone;
				 		}
		 			}
					
					//Cylinder
		 			else if (word.compare("cylinder") == 0){
			 			datei >> name;
						
			 			if(shape_map.find(name) == shape_map.end()){
				 			float x,y,z,r;
				 			
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 center1(x,y,z);
				 			sstr.clear();

				 			datei >> word;
				 			sstr << word;
				 			sstr >> r;
				 			sstr.clear();

				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word << ' ';
				 			datei >> word;
				 			sstr << word;
				 			sstr >> x >> y >> z;
				 			glm::vec3 center2(x,y,z);
				 			sstr.clear();
				 			
				 			datei >> word; // Material name

				 			std::shared_ptr<Shape> cyl(new Cylinder(name, center1, r, center2, word));
							//WEG?
				 			//s.shapes.push_back(cyl);

				 			//Cylinder cyl(name, center1, r, center2, word);
				 			shape_map[name] = cyl;
				 		}
		 			}
					
					//Composite
		 			else if (word.compare("composite") == 0){
		 				std::shared_ptr<Composite> c(new Composite);
		 				datei >> word;
		 				std::map<std::string, std::shared_ptr<Shape>>::iterator i= shape_map.begin();
		 				while((word.compare("#") != 0 && word.compare("render") 
		 					!= 0 && word.compare("camera") != 0 && 
		 					word.compare("define") != 0) && i != shape_map.end()){
		 		
		 					std::shared_ptr<Shape> p = shape_map[word];
		 					//p = (shape_map.find(word)->second);
		 					c->add(p);
		 					datei >> word;
		 					++i;
		 				}
		 				s.shape_composite.push_back(c);
		 			}
	 			}
	 			/*
	 			else{
	 				//define <class> <name> <arg> ...
	 				//Für evtl neue Klassen
	 			}*/
	 			sstr.clear(); 
		 		
	 		}	
		}

		//calculate ambient from all light sources
		for (std::vector<Light_source>::const_iterator it = s.lights.begin(); it != s.lights.end(); ++it){
			s.ambient.r += (*it).get_ambiente().r;
			s.ambient.g += (*it).get_ambiente().g;
			s.ambient.b += (*it).get_ambiente().b;
		}
 	}
	
 	else{
 		std::cout << "File not good" << std::endl;
 	}

 	//datei.close();
 	return s;

 }
