#include <iostream>
#include <string>
#include <fstream> 
#include "sdf_loader.hpp"
#include "scene.hpp"
#include "material.hpp"
#include <map>
using namespace std;

Sdf_loader::Sdf_loader(std::string file): file_{file} {}
Sdf_loader::Sdf_loader():file_{""} {}
Sdf_loader::~Sdf_loader(){}

Scene Sdf_loader::loadScene(std::file) const{

	ifstream datei(“mat.txt“, ios::in);
 	Scene s{};
 	if (datei.good())
 	{
 		while(getline(datei, line)){
 			//compare(pos,leng,string)
 			if (line.compare(0,1,"#") == 0)//Kommentarzeilen werden ignoriert
	 		{
	 			//do nothing BRAUCHEN WIR DAS??
	 		}
	 		else if (line.compare(0,6,"camera") == 0)//Kamera
	 		{
	 			/* code */
	 		}
	 		else if (line.compare(0,6,"render") == 0)//Renderer
	 		{
	 			/* code */
	 		}
	 		else if (line.compare(0,6,"define") == 0)//Klassendefinierung
	 		{
	 			if (line.compare(7,8,"material") == 0)//Materials für Shapes
		 		{
		 			/* code */
		 		}
		 		else if (line.compare(7,5,"light") == 0)//Lichquellen
		 		{
		 			/* code */
		 		}
	 			else if ("define shape box")//Shapes (Box)
		 		{
		 			/* code */
		 		}
		 		else if ("define shape shpere")//Shapes (Sphere)
		 		{
		 			/* code */
		 		}
		 		
	 		}	
 		}
 	
 		


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