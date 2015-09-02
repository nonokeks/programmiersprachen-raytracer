#ifndef BUW_CONE_HPP
#define BUW_CONE_HPP

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <string>

#include "color.hpp"
#include "shape.hpp"
#include "ray.hpp"

class Cone: public Shape{
	public:
		Cone();
		Cone(glm::vec3 const& center, float radius, glm::vec3 const& center2);
		Cone(std::string name, glm::vec3 const& center, float radius, 
			 glm::vec3 const& center2, std::string material);
		
		glm::vec3 const& get_center() const;
		float const& get_radius() const;
		glm::vec3 const& get_center2() const;
		
		bool intersect(Ray const& ray, float& distance, 
			           glm::vec3& intersection, glm::vec3& normal)const;

		/*virtual*/ std::ostream& print(std::ostream& os) const;

	private:
		glm::vec3 center_; //Center of base
		float radius_;
		glm::vec3 center2_; // Top
};

#endif // #ifndef BUW_CONE_HPP