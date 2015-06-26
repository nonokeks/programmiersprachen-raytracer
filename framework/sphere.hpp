#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include <iostream>
#include <string>
#include "color.hpp"

class Sphere : public Shape
{
public:
	Sphere();
	Sphere(glm::vec3 const& center, float radius);
	Sphere(glm::vec3 const& center, float radius, std::string name, Color color);
	

	glm::vec3 const& get_center() const;
	float get_radius() const;

	/*virtual*/ float area() const;
	/*virtual*/ float volume() const;
	/*virtual*/ std::ostream& print(std::ostream& os) const;

private:
	glm::vec3 center_;
	float radius_;
};

#endif // #ifndef BUW_SPHERE_HPP