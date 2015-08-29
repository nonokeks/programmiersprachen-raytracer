#include "material.hpp"
#include <iostream>
#include <string>
#include "color.hpp"

Material::Material():
	name_{""},
	ka_{0.0, 0.0, 0.0},
	kd_{0.0, 0.0, 0.0},
	ks_{0.0, 0.0, 0.0},
	m_{0.0f}{}

Material::Material(std::string name, Color const& ka, Color const& kd, 
	Color const& ks, float m, float refract, float opacity):
	name_{name},
	ka_{ka},
	kd_{kd},
	ks_{ks},
	m_{m},
	refract_{refract}
	opacity_{opacity}{}

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
float Material::get_refract() const{
	return refract_;
}
float Material::get_opacity() const{
	return opacity_;
}

//operator<<
std::ostream& operator<<(std::ostream& os, Material const& mat){
	os << "Materialname: " << mat.name_ << " ka: " << mat.ka_.r << " " << mat.ka_.g << " " << mat.ka_.b << "\n";
	os << "kd: " << mat.kd_.r << " " << mat.kd_.g << " " << mat.kd_.b << " ks: "<< mat.ks_.r << " " << mat.ks_.g << " " << mat.ks_.b << "\n";
	os << "m: " << mat.m_;
	return os;
}
