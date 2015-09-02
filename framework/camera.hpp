#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/mat4x4.hpp> // glm::mat4
#include <math.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp> // glm::vec4
#include <string>
#include <vector>

#include "ray.hpp"
#include "pixel.hpp"

class Camera {
	public:
		Camera(std::string name, float fov_x);
		Camera(std::string name, float fov_x, glm::vec3 const& eye_, 
			   glm::vec3 const& dir_, glm::vec3 const& up_);
		Camera();
		~Camera();

		Camera& operator= (Camera const& rhs);

		std::string get_name() const;
		float get_angle() const;
		glm::vec3 get_position() const; 
		glm::vec3 get_direction() const; 
		glm::vec3 get_up() const;

		void generate_rays(unsigned width, unsigned height, 
							std::vector<Ray>& rays);

	private:
		std::string name_;
		float fov_x_;
		glm::vec3 eye_; // Position in space
		glm::vec3 dir_; // line of sight
		glm::vec3 up_; // Up-Vector
};

#endif
