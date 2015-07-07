#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#include <iostream>
#include <string>
#include "scene.hpp"
#include <fstream> 
#include "material.hpp"
#include <map>
using namespace std;

class Sdf_loader
{
public:
	Sdf_loader(std::string file);
	Sdf_loader();
	~Sdf_loader();

	//Scene loadScene(std::file) const;
	
	void loadMaterial(std::string file, std::map<std::string, Material>& material );

private:
	std::string file_;

};


#endif // #ifndef BUW_SHAPE_HPP