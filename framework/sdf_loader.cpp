#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  
#include <glm/vec3.hpp>
#include "sdf_loader.hpp"
#include "scene.hpp"
#include "material.hpp"
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
#include <map>
using namespace std;

Sdf_loader::Sdf_loader(std::string file): file_{file} {}
Sdf_loader::Sdf_loader():file_{""} {}
Sdf_loader::~Sdf_loader(){}

Scene Sdf_loader::load_scene(std::string file) const{
	//file_ = file; // noetig?

	ifstream datei(file, ios::in);
 	Scene s{};
 	std::string line;
 	std::string word = " ";
 	std::string name = " ";
 	std::stringstream sstr; //für String to Float
 	if (datei.good())
 	{

		while(datei >> word){

 			if (word.compare("#") == 0)//Kommentarzeilen werden ignoriert
	 		{
	 			datei >> word; // Nächstes Word wird eingelesen und somit die Zeile ignoriert

	 			//Komplette Zeile automatisch?

	 			/*
	 			if(word.compare("camera") == 0 ||
				   word.compare("render") == 0 || word.compare("define") == 0){
	 			    
	 			    //datei >> word;
	 			}*/
	 			
	 		}
	 		else if (word.compare("camera") == 0)//Kamera
	 		{
	 			
	 			datei >> name;
	 			datei >> word;
	 			//String to Float
				sstr << word; 
				float angle;
				sstr >> angle;
				sstr.clear();

				datei >> word;
			
				if (word.compare("#") != 0 && word.compare("render") != 0 && 
				   word.compare("ambient") != 0 && word.compare("define") != 0)
				{

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
	 		else if (word.compare("render") == 0)//Renderer
	 		{
	 			datei >> name; //Kamera Name ..?
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
	 		else if (word.compare("define") == 0)//Klassendefinierung
	 		{
	 			datei >> word;
	 			if (word.compare("material") == 0)//Materials für Shapes
		 		{
		 			float r,g,b;
		 			datei >> name;
		 			//nur wenn matname eindeutig
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
		 		else if (word.compare("light") == 0)//Lichquellen
		 		{
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
	 			else if (word.compare("shape") == 0)
	 			{
	 				datei >> word;
	 				if (word.compare("box") == 0)//Shapes (Box)
			 		{
			 			datei >> name;
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
			 			
			 			datei >> word; //Materialname

			 			std::shared_ptr<Shape> b(new Box(name, min, max, word));
			 			s.shapes.push_back(b);

			 		}
			 		else if (word.compare("sphere") == 0)//Shapes (Sphere)
			 		{
			 			datei >> name;
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

			 			datei >> word;//Materialname

			 			std::shared_ptr<Shape> sph(new Sphere(name, center, r, word));
			 			s.shapes.push_back(sph);
		 			}
		 			else if (word.compare("triangle") == 0)//Shapes (Sphere)
			 		{
			 			datei >> name;
			 			float x,y,z;
			 			
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
			 			
			 			datei >> word;//Materialname

			 			std::shared_ptr<Shape> tri(new Triangle(name, a, b, c, word));
			 			s.shapes.push_back(tri);
		 			}
		 			else if (word.compare("cone") == 0)//Shapes (Sphere)
			 		{
			 			datei >> name;
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
			 			
			 			datei >> word;//Materialname

			 			std::shared_ptr<Shape> cone(new Cone(name, center1, r, center2, word));
			 			s.shapes.push_back(cone);
		 			}
		 			else if (word.compare("cylinder") == 0)//Shapes (Sphere)
			 		{
			 			datei >> name;
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
			 			
			 			datei >> word;//Materialname

			 			std::shared_ptr<Shape> cyl(new Cylinder(name, center1, r, center2, word));
			 			s.shapes.push_back(cyl);
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

		//Ambiente berechnen aus allen Lichtquellen

		for (std::vector<Light_source>::const_iterator it = s.lights.begin(); it != s.lights.end(); ++it)
		{
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
