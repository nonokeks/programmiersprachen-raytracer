#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
//#include "material.hpp"

class Sphere : public Shape
{
public:
	Sphere();
	Sphere(glm::vec3 const& center, float radius);
	Sphere(std::string name, glm::vec3 const& center, float radius, std::string material);
	//Sphere(glm::vec3 const& center, float radius, std::string name, Color const& color);
	//~Sphere();
	//Sphere(glm::vec3 const& center, float radius, std::string name, Material const& mat);
	//Sphere(glm::vec3 const& center, float radius, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m);

	glm::vec3 const& get_center() const;
	float get_radius() const;
	bool intersect(Ray const& ray, float& distance)const;
	bool intersect(Ray const& ray, float& distance, Optional_hit& o)const;

	/*virtual*/ float area() const;
	/*virtual*/ float volume() const;
	/*virtual*/ std::ostream& print(std::ostream& os) const;

private:
	glm::vec3 center_;
	float radius_;
};

#endif // #ifndef BUW_SPHERE_HPP
