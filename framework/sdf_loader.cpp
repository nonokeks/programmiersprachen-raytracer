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
#include <map>
using namespace std;

Sdf_loader::Sdf_loader(std::string file): file_{file} {}
Sdf_loader::Sdf_loader():file_{""} {}
Sdf_loader::~Sdf_loader(){}

Scene Sdf_loader::loadScene(std::string file) const{

	ifstream datei(file, ios::in);
 	Scene s{};
 	//std::string line;
 	std::string word;
 	std::string name;
 	std::stringstream sstr; //für String to Float
 	if (datei.good())
 	{
 		//while(getline(datei, line)){
 			

			while(datei >> word){
 			if (word.compare("#") == 0)//Kommentarzeilen werden ignoriert
	 		{
	 			//do nothing BRAUCHEN WIR DAS??
	 		}
	 		else if (word.compare("camera") == 0)//Kamera
	 		{
	 			datei >> name;
	 			datei >> word;
	 			//String to Float
				sstr << word; 
				float ancle; 
				sstr >> ancle;

				Camera c{name, ancle};
				s.cam = c;

	 		}
	 		else if (word.compare("render") == 0)//Renderer
	 		{
	 			datei >> name; //Kamera Name ..?
	 			std::string filename;
	 			datei >> filename;

	 			unsigned x_res;
	 			unsigned y_res;
	 			datei >> word;
	 			sstr << word;
	 			sstr >> x_res;
	 			datei >> word;
	 			sstr << word;
	 			sstr >> y_res;

	 			Renderer render{x_res, y_res, filename};
	 			s.render = render;
	 		}
	 		else if (word.compare("define") == 0)//Klassendefinierung
	 		{
	 			datei >> word;
	 			if (word.compare("material") == 0)//Materials für Shapes
		 		{
		 			datei >> name;
		 			Color ka();
		 			//red
		 			datei >> word;
		 			sstr << word;
		 			sstr >> ka.r;
		 			//green
		 			datei >> word;
		 			sstr << word;
		 			sstr >> ka.g;
		 			//blue
		 			datei >> word;
		 			sstr << word;
		 			sstr >> ka.b;

		 			Color kd();
		 			//red
		 			datei >> word;
		 			sstr << word;
		 			sstr >> kd.r;
		 			//green
		 			datei >> word;
		 			sstr << word;
		 			sstr >> kd.g;
		 			//blue
		 			datei >> word;
		 			sstr << word;
		 			sstr >> kd.b;

		 			Color ks();
		 			//red
		 			datei >> word;
		 			sstr << word;
		 			sstr >> ks.r;
		 			//green
		 			datei >> word;
		 			sstr << word;
		 			sstr >> ks.g;
		 			//blue
		 			datei >> word;
		 			sstr << word;
		 			sstr >> ks.b;

		 			float m;
		 			datei >> word;
		 			sstr << word;
		 			sstr >> m;

		 			Material mat{name, ka, kd, ks, m};
				    s.material[name] = mat;


		 		}
		 		else if (word.compare("light") == 0)//Lichquellen
		 		{
		 			datei >> name;

		 			float x,y,z;
		 			//x
		 			datei >> word;
		 			sstr << word;
		 			sstr >> x;
		 			//y
		 			datei >> word;
		 			sstr << word;
		 			sstr >> y;
		 			//z
		 			datei >> word;
		 			sstr << word;
		 			sstr >> z;
		 			glm::vec3 position(x,y,z);

		 			float ld, la;
		 			//la
		 			datei >> word;
		 			sstr << word;
		 			sstr >> la;
		 			//ld
		 			datei >> word;
		 			sstr << word;
		 			sstr >> ld;
		 			Light_source light(name, position, la, ld);
		 			s.lights.push_back(light);

		 		}
	 			else if (word.compare("shape") == 0)
	 			{
	 				datei >> word;
	 				if (word.compare("box") == 0)//Shapes (Box)
			 		{
			 			//Scene hat Shared pointer? 
			 		}
			 		else if (word.compare("shpere") == 0)//Shapes (Sphere)
			 		{
			 			/* code */
		 			}
	 			}
	 			else{
	 				//define <class>...
	 			}
		 		
	 		}	
			}

 			/*
 			//compare(pos,leng,string)
 			if (line.compare(0,1,"#") == 0)//Kommentarzeilen werden ignoriert
	 		{
	 			//do nothing BRAUCHEN WIR DAS??
	 		}
	 		else if (line.compare(0,6,"camera") == 0)//Kamera
	 		{
	 			
	 		}
	 		else if (line.compare(0,6,"render") == 0)//Renderer
	 		{
	 			
	 		}
	 		else if (line.compare(0,6,"define") == 0)//Klassendefinierung
	 		{
	 			if (line.compare(7,8,"material") == 0)//Materials für Shapes
		 		{
		 			
		 		}
		 		else if (line.compare(7,5,"light") == 0)//Lichquellen
		 		{
		 			
		 		}
	 			else if ("define shape box")//Shapes (Box)
		 		{
		 			
		 		}
		 		else if ("define shape shpere")//Shapes (Sphere)
		 		{
		 			
		 		}
		 		
	 		}*/
 		//}
 	
 		


 	}

 	//datei.close();
 	return s;

 }
	
void Sdf_loader::load_material(std::string file, std::map<std::string, Material>& material) {
	ifstream datei;
	datei.open(file, ios::in);
	std::string line;
	std::string name;
	std::string defmat = "define material";
	if (datei.good())
	{
		std::cout<<"geöffnet"<<std::endl;
	
		while(getline(datei, line)){
			if(defmat.compare(0, 14, line) == 0){
				int i = 15;
				for (i; line[i]==' '; ++i)
				{
					name += line[i];
					
				}
				//int c = 3;
				
			
				//ka
				std::string temp;
				float ka_r;
				float ka_g;
				float ka_b;
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				ka_r=stod(temp);
				temp.clear(); 
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				ka_b = stod(temp);
				temp.clear();
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				ka_b = stod(temp);
				temp.clear();
				
				//ks
				float kd_r;
				float kd_g;
				float kd_b;
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				kd_r=stod(temp);
				temp.clear(); 
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				kd_b = stod(temp);
				temp.clear();
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				kd_b = stod(temp);
				temp.clear();

				//kd
				float ks_r;
				float ks_g;
				float ks_b;
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				ks_r=stod(temp);
				temp.clear(); 
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				ks_b = stod(temp);
				temp.clear();
				while (line[i]!=' ')
				{
					temp += line[i];
					++i;
				}
				ks_b = stod(temp);
				temp.clear();


				Color ka{ka_r, ka_g, ka_b};
				Color kd{kd_r, kd_g, kd_b};
				Color ks{ks_r, ks_g, ks_b};

				while (i<line.size())
				{
					temp += line[i];
					++i;
				}
				float m = stod(temp);

				Material mat{name, ka, kd, ks, m};
				material[name] = mat;

			}
			else{
				break;
			}
		}
	}
	else{
		std::cout<<"Datei kaputt"<<std::endl;
	}
	datei.close();
}

std::string Sdf_loader::get_file() const{
	return file_;
}