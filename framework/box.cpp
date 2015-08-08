#include "box.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"

Box::Box() : Shape{}, min_{0.0f, 0.0f, 0.0f}, max_{0.0f, 0.0f, 0.0f} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max):Shape{}, min_{min}, max_{max} {}
// Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color const& color):Shape{name, color}, min_{min}, max_{max} {}
//Box::~Box(){std::cout << "Box Destructor" << std::endl;}

/*Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Material const& mat):Shape{name, mat}, min_{min}, max_{max} {}
Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks,
float m):Shape{name, name_mat, ka, kd, ks, m}, min_{min}, max_{max} {}*/

Box::Box(std::string name, glm::vec3 const& min, glm::vec3 const& max, std::string material):Shape{name, material}, 
min_{min}, max_{max} {}


glm::vec3 const& Box::get_min()const{
	return min_;
}
glm::vec3 const& Box::get_max()const{
	return max_;
}


float Box::area() const{
	float depth = fabs(max_.x - min_.x);
	float width = fabs(max_.y - min_.y);
	float high = fabs(max_.z - min_.z);
	return (2 * high * width + 2 * width * depth + 2 * high * depth) ;
}
float Box::volume() const{
	float depth = fabs(max_.x - min_.x);
	float width = fabs(max_.y - min_.y);
	float high = fabs(max_.z - min_.z);
	return (high * width * depth);
}

std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
	//os << "Name: " << get_name() << ", Color: " << get_color().r << " " << get_color().g << " " << get_color().b << "\n";
	os << "Min: " << min_.x << " " << min_.y << " " << min_.z << ", Max: "<< max_.x << " " << max_.y << " " << max_.z;
	return os;
}

bool Box::intersect(Ray const& ray, float& distance) const{
    double a = (get_min().x - ray.origin.x) * ray.inv_direction.x;
    double b = (get_max().x - ray.origin.x) * ray.inv_direction.x;
    double tmin = std::min(a, b);
    double tmax = std::max(a, b);

    a = (get_min().y - ray.origin.y) * ray.inv_direction.y;
    b = (get_max().y - ray.origin.y) * ray.inv_direction.y;
    tmin = std::max(tmin, std::min(a, b));
    tmax = std::min(tmax, std::max(a, b));

    a = (get_min().z - ray.origin.z) * ray.inv_direction.z;
    b = (get_max().z - ray.origin.z) * ray.inv_direction.z;
    tmin = std::max(tmin, std::min(a, b));
    tmax = std::min(tmax, std::max(a, b));

    if (tmax > std::max(0.0, tmin)) {
        distance = sqrt(tmin * tmin * (ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z));
        return true;
    }
    return false;
}
