#include "camera.hpp"

Camera::Camera(std::string name, float fov_x):
	name_{name},
	fov_x_{fov_x},
	eye_{0.0,0.0,0.0},
	dir_{0.0,0.0,-1},
	up_{0.0,1,0.0}{}
	
Camera::Camera(std::string name, float fov_x, glm::vec3 const& position,
			   glm::vec3 const& direction, glm::vec3 const& up):
	name_{name},
	fov_x_{fov_x},
	eye_{position},
	dir_{direction},
	up_{up}{}
	
Camera::Camera():
	name_{""},
	fov_x_{0.0f},
	eye_{0.0,0.0,0.0},
	dir_{0.0,0.0,-1},
	up_{0.0,1,0.0}{}
	
Camera::~Camera(){}

std::string Camera::get_name() const{
	return name_;
}
float Camera::get_angle() const{
	return fov_x_;
}
glm::vec3 Camera::get_position() const{
	return eye_;
}
glm::vec3 Camera::get_direction() const{
	return dir_;
} 
glm::vec3 Camera::get_up() const{
	return up_;
}

Camera& Camera::operator= (Camera const& rhs){
	name_ = rhs.get_name();
	fov_x_ = rhs.get_angle();
	eye_ = rhs.get_position(); 
    dir_ = rhs.get_direction();
	up_ = rhs.get_up();
	return *this;
}


void Camera::generate_rays(unsigned width, unsigned height, 
							std::vector<Ray> & rays)
{
	float distance = ((width/2) / tan(fov_x_ * M_PI / 360)); 

	for (int y = ((int)height/-2); y < (int)height/2; ++y)
	{
		for (int x = ((int)width/-2); x < (int)width/2; ++x)
		{
			glm::vec3 direction(x, y, -(distance));
			
			//Scale Camera if not default
			if (eye_.x != 0 || eye_.y != 0 || eye_.z != 0 ||
				dir_.x != 0 || dir_.y != 0 || dir_.z != -1 ||
				up_.x != 0 || up_.y != 1 || up_.z != 0 )
			{
				glm::vec4 direct_temp(x, y, -(distance), 1);
				glm::vec3 u = glm::normalize(glm::cross(dir_, up_));
				glm::vec3 v = glm::normalize(glm::cross(u, dir_));
				dir_ = glm::normalize(dir_);
				// Matrix is implemented column x row
				glm::mat4 matrix(u.x, u.y, u.z, 0,
								 v.x, v.y, v.z, 0,
								 (dir_.x*-1), (dir_.y*-1), (dir_.z*-1),0,
								 eye_.x, eye_.y, eye_.z, 1);
				// Matrix x Vector
				glm::vec4 new_direct = matrix * direct_temp;

				direction.x = new_direct.x;
				direction.y = new_direct.y;
				direction.z = new_direct.z;
			}

			Ray temp_ray(eye_, direction);
			rays.push_back(temp_ray);
		}
	}
}