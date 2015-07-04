#include "material.hpp"
#include <iostream>
#include <string>
#include "color.hpp"

Material::Material(): name_{""}, ka_{0.0, 0.0, 0.0}, kd_{0.0, 0.0, 0.0}, ks_{0.0, 0.0, 0.0}, m_{0.0f}{}
Material::Material(std::string name, Color const& ka, Color const& kd, Color const& ks, float m): name_{name}, 
ka_{ka}, kd_{kd}, ks_{ks}, m_{m}{}
Material::~Material(){}
//getter
std::string const& Material::get_name()const{
	return name_;
}
Color const& Material::get_ka() const{
	return ka_;
}
Color const& Material::get_kd() const{
	return kd_;
}
Color const& Material::get_ks() const{
	return ks_;
}
float Material::get_m() const{
	return m_;
}

//operator<<
friend std::ostream& Material::operator<<(std::ostream& os, Material const& mat){
	//Fehlt noch
	return os;
}