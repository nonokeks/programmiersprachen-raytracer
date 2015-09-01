#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

#include "color.hpp"
//#include "material.hpp"
#include "ray.hpp"
#include "shape.hpp"

class Sphere: public Shape{
	public:
		Sphere();
		Sphere(glm::vec3 const& center, float radius);
		Sphere(std::string name, glm::vec3 const& center, float radius, std::string material);
		//DELETE?
		//Sphere(glm::vec3 const& center, float radius, std::string name, Color const& color);
		//~Sphere();
		//Sphere(glm::vec3 const& center, float radius, std::string name, Material const& mat);
		//Sphere(glm::vec3 const& center, float radius, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m);

		glm::vec3 const& get_center() const;
		float get_radius() const;
		//bool intersect(Ray const& ray, float& distance)const;
		bool intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const;

		// /*virtual*/ float area() const;
		// /*virtual*/ float volume() const;
		/*virtual*/ std::ostream& print(std::ostream& os) const;

	private:
		glm::vec3 center_;
		float radius_;
};

#endif // #ifndef BUW_SPHERE_HPP
