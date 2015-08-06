#include "camera.hpp"
#include <string>

Camera::Camera(std::string name, float fov_x): name_{name}, fov_x_{fov_x}{}
Camera::Camera(): name_{""}, fov_x_{0.0f}{}
Camera::~Camera(){}