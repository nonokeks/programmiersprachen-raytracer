#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP 
#include <string>
#include <vector>
#include "ray.hpp"
#include <glm/vec3.hpp>



class Camera
{
public:
	Camera(std::string name, float fov_x);
	Camera(std::string name, float fov_x, glm::vec3 const& eye_, glm::vec3 const& dir_, glm::vec3 const& up_);
	Camera();
	~Camera();

	Camera& operator= (Camera const& rhs);

	//getter
	std::string get_name() const;
	float get_angle() const;
	glm::vec3 get_position() const; 
	glm::vec3 get_direction() const; 
	glm::vec3 get_up() const;

	void generate_rays(unsigned width, unsigned height, std::vector<Ray>& rays);

private:
	std::string name_;
	float fov_x_;
	glm::vec3 eye_; //Position im Raum
	glm::vec3 dir_; //Blickrichtung
	glm::vec3 up_;//Up-Vector
};





#endif
