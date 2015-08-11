#include "camera.hpp"
#include <string>
#include <math.h>
#include <vector>
#include "ray.hpp"
#include "pixel.hpp"
#include <glm/vec3.hpp>

Camera::Camera(std::string name, float fov_x): name_{name}, fov_x_{fov_x}{}
Camera::Camera(): name_{""}, fov_x_{0.0f}{}
Camera::~Camera(){}

std::string Camera::get_name() const{
	return name_;
}
float Camera::get_angle() const{
	return fov_x_;
}

Camera& Camera::operator= (Camera const& rhs){
	name_ = rhs.get_name();
	fov_x_ = rhs.get_angle();
	return *this;
}

void Camera::generate_rays(unsigned width, unsigned height, std::vector<Ray> & rays){
	float distance = ((width/2) / tan(fov_x_ * M_PI / 360)); 
	glm::vec3 origin(0,0,0);

	for (unsigned y = -(height/2); y < height/2; ++y)
	{
		for (unsigned x = -(width/2); x < width/2; ++x)
		{
			glm::vec3 direction(float(x), float(y), -(distance));
			Ray temp_ray(origin, direction);
			rays.push_back(temp_ray);
		}
	}
}
