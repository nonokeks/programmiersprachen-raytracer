#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

#include "color.hpp"
#include "ray.hpp"
#include "shape.hpp"

class Sphere: public Shape{
	public:
		Sphere();
		Sphere(glm::vec3 const& center, float radius);
		Sphere(std::string name, glm::vec3 const& center, float radius, 
			std::string material);
		
		glm::vec3 const& get_center() const;
		float get_radius() const;
		bool intersect(Ray const& ray, float& distance, 
					glm::vec3& intersection, glm::vec3& normal)const;

		
		/*virtual*/ std::ostream& print(std::ostream& os) const;

	private:
		glm::vec3 center_;
		float radius_;
};

#endif // #ifndef BUW_SPHERE_HPP
