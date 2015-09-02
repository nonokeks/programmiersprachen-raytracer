#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

#include "color.hpp"
#include "shape.hpp"
#include "ray.hpp"

class Triangle: public Shape{
public:
	Triangle();
	Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c);
	Triangle(std::string name, glm::vec3 const& a, glm::vec3 const& b, 
			glm::vec3 const& c, std::string material);
	
	glm::vec3 const& get_a() const;
	glm::vec3 const& get_b() const;
	glm::vec3 const& get_c() const;
	
	bool intersect(Ray const& ray, float& distance, glm::vec3& intersection,
				 glm::vec3& normal)const;

	/*virtual*/ std::ostream& print(std::ostream& os) const;

private:
	glm::vec3 a_;
	glm::vec3 b_;
	glm::vec3 c_;
};

#endif // #ifndef BUW_TRIANGLE_HPP