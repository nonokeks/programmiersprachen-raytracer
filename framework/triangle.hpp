#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
//#include "material.hpp"

class Triangle : public Shape
{
public:
	Triangle();
	Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c);
	Triangle(std::string name, glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, std::string material);
	
	//Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, std::string name, Color const& color);
	//~Triangle();
	//Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, std::string name, Material const& mat);
	//Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m);

	glm::vec3 const& get_a() const;
	glm::vec3 const& get_b() const;
	glm::vec3 const& get_c() const;
	
	bool intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const;

	/*virtual*/ std::ostream& print(std::ostream& os) const;

private:
	glm::vec3 a_;
	glm::vec3 b_;
	glm::vec3 c_;
};

#endif // #ifndef BUW_TRIANGLE_HPP