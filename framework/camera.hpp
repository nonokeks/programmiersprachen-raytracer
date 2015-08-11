#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP 
#include <string>
#include <vector>
#include "ray.hpp"


class Camera
{
public:
	Camera(std::string name, float fov_x);
	Camera();
	~Camera();

	Camera& operator= (Camera const& rhs);

	//getter
	std::string get_name() const;
	float get_angle() const;

	void generate_rays(unsigned width, unsigned height, std::vector<Ray> & rays);

private:
	std::string name_;
	float fov_x_;
};





#endif
