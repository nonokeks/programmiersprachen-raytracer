#include "camera.hpp"
#include <string>

Camera::Camera(std::string name, float fov_x): name_{name}, fov_x_{fov_x}{}
Camera::Camera(): name_{""}, fov_x_{0.0f}{}
Camera::~Camera(){}

std::string Camera::get_name() const{
	return name_;
}
float Camera::get_ancle() const{
	return fov_x_;
}

Camera& Camera::operator= (Camera const& rhs){
	name_ = rhs.get_name();
	fov_x_ = rhs.get_ancle();
	return *this;
}
