#include "sphere.hpp"

#define _USE_MATH_DEFINES

Sphere::Sphere():
	Shape{},
	center_{0.0f, 0.0f, 0.0f},
	radius_{0.0}{}
	
Sphere::Sphere(glm::vec3 const& center, float radius):
	Shape{},
	center_{center},
	radius_{radius}{}
	
Sphere::Sphere(std::string name, glm::vec3 const& center, float radius, 
			   std::string material):
	Shape{name, material},
	center_{center},
	radius_{radius}{}
	
	
glm::vec3 const& Sphere::get_center() const {
	return center_;
}

float Sphere::get_radius() const{
	return radius_;
}


bool Sphere::intersect(Ray const& ray, float& distance, 
						glm::vec3& intersection, glm::vec3& normal)const
{
	glm::vec3 direct = glm::normalize(ray.direction);
	bool b = glm::intersectRaySphere(ray.origin, direct, center_, radius_,
									 intersection, normal);
	normal = glm::normalize(normal);
	return b;
}

std::ostream& Sphere::print(std::ostream& os) const{
	Shape::print(os);
	
	os << "Radius: " << radius_ << ", Center: " << center_.x << " " <<
	   center_.y << " " << center_.z;

	return os;
}
