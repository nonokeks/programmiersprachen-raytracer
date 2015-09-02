#include "triangle.hpp"

#define _USE_MATH_DEFINES


Triangle::Triangle():
	Shape{},
	a_{0.0f, 0.0f, 0.0f},
	b_{0.0f, 0.0f, 0.0f},
	c_{0.0f, 0.0f, 0.0f}{}
	
Triangle::Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c):
	Shape{},
	a_{a},
	b_{b},
	c_{c}{}
	
Triangle::Triangle(std::string name, glm::vec3 const& a, glm::vec3 const& b, 
					glm::vec3 const& c, std::string material):
	Shape{name, material},
	a_{a},
	b_{b},
	c_{c}{}

glm::vec3 const& Triangle::get_a() const {
	return a_;
}

glm::vec3 const& Triangle::get_b() const {
	return b_;
}

glm::vec3 const& Triangle::get_c() const {
	return c_;
}

bool Triangle::intersect(Ray const& ray, float& distance, 
						glm::vec3& intersection, glm::vec3& normal)const{
	normal = glm::normalize(glm::cross(a_ - b_, a_ - c_)); 
	if(glm::dot(normal, ray.direction) > 0) {
		normal *= -1;
	}
	
	glm::vec3 direct = glm::normalize(ray.direction);
	distance = (glm::dot(a_,normal) - glm::dot(normal,ray.origin)) /
				 glm::dot(direct, normal);
	return glm::intersectLineTriangle(ray.origin, direct, a_, b_, c_,
									 intersection);
}

std::ostream& Triangle::print(std::ostream& os) const{
	Shape::print(os);
	
	os << "Point A: " << a_.x << " " << a_.y << " " << a_.z << ",";
	os << "Point B: " << b_.x << " " << b_.y << " " << b_.z << ",";
	os << "Point C: " << c_.x << " " << c_.y << " " << c_.z;

	return os;
}
