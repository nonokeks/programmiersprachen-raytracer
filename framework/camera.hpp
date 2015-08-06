#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP 
#include <string>
class Camera
{
public:
	Camera(std::string name, float fov_x);
	Camera();
	~Camera();

private:
	std::string name_;
	float fov_x_;
};





#endif