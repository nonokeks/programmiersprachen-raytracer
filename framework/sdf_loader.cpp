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

// Scene Sdf_loader::loadScene(std::file) const{

// 	//fstream textfile(“mat.txt“, ios::in);
// 	Scene s{};


// 	//textfile.close();
// 	return s;

// }
	
void Sdf_loader::loadMaterial(std::string file, std::map<std::string, Material>& material) {
	ifstream textfile;
	textfile.open(file, ios::in);
	std::string line;
	std::string name;
	std::string defmat = "define material";
	while(getline(textfile, line)){
		if(defmat.compare(0, 15, line)){
			int i = 16;
			for (i; line[i]==' '; ++i)
			{
				name += line[i];
			}
			int c = 3;
			
		
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
	
	textfile.close();
}

std::string Sdf_loader::get_file()const{
	return file_;
}