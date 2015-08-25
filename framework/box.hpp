#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
//#include "material.hpp"

class Box : public Shape
{
public:
	Box();
	Box(glm::vec3 const& min, glm::vec3 const& max);
	// Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color const& color);
	//~Box();
	//Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Material const& mat);
	//Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m);

	Box(std::string name,glm::vec3 const& min, glm::vec3 const& max, std::string material);

	glm::vec3 const& get_min()const;
	glm::vec3 const& get_max()const;
	

	/*virtual*/ float area() const;
	/*virtual*/ float volume() const;
	/*virtual*/ std::ostream& print(std::ostream& os) const;

	bool intersect(Ray const& ray, float& distance) const;
	bool intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal) const;

private:
	glm::vec3 min_;
	glm::vec3 max_;

};


#endif //  #ifndef BUW_BOX_HPP
