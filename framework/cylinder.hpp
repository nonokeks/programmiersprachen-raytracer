#ifndef BUW_CYLINDER_HPP
#define BUW_CYLINDER_HPP

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <string>

#include "color.hpp"
//#include "material.hpp"
#include "shape.hpp"
#include "ray.hpp"

class Cylinder: public Shape{
	public:
		Cylinder();
		Cylinder(glm::vec3 const& center, float radius, glm::vec3 const& center2);
		Cylinder(std::string name, glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string material);
		
		//delete?
		//Cylinder(glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string name, Color const& color);
		//~Cylinder();
		//Cylinder(glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string name, Material const& mat);
		//Cylinder(glm::vec3 const& center, gfloat radius, glm::vec3 const& center2, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m);

		glm::vec3 const& get_center() const; 
		glm::vec3 const& get_center2() const;
		float const& get_radius() const;
		
		//bool intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const;


		/*virtual*/ std::ostream& print(std::ostream& os) const;

	private:
		glm::vec3 center_;	// Center of base disk
		float radius_;
		glm::vec3 center2_; // Center of top disk
};

#endif // #ifndef BUW_CYLINDER_HPP