#ifndef BUW_CYLINDER_HPP
#define BUW_CYLINDER_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
//#include "material.hpp"

class Cylinder : public Shape
{
public:
	Cylinder();
	Cylinder(glm::vec3 const& center, float radius, float height);
	Cylinder(std::string name, glm::vec3 const& center, float radius, float height, std::string material);
	
	//Cylinder(glm::vec3 const& center, float radius, float height, std::string name, Color const& color);
	//~Cylinder();
	//Cylinder(glm::vec3 const& center, float radius, float height, std::string name, Material const& mat);
	//Cylinder(glm::vec3 const& center, gfloat radius, float height, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m);

	glm::vec3 const& get_center() const; //Basis Mittelpunkt
	glm::vec3 const& get_center2() const; //oberer Mittelpunkt
	float const& get_radius() const;
	
	bool intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const;

	/*virtual*/ std::ostream& print(std::ostream& os) const;

private:
	glm::vec3 center_;
	glm::vec3 center2_;
	float radius_;
	
};

#endif // #ifndef BUW_CYLINDER_HPP