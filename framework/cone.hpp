#ifndef BUW_CONE_HPP
#define BUW_CONE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
//#include "material.hpp"

class Cone : public Shape
{
public:
	Cone();
	Cone(glm::vec3 const& center, float radius, glm::vec3 const& center2);
	Cone(std::string name, glm::vec3 const& center, float radius, glm::vec3 const& center2, std::string material);
	
	//Cone(glm::vec3 const& center, float radius, float height, std::string name, Color const& color);
	//~Cone();
	//Cone(glm::vec3 const& center, float radius, float height, std::string name, Material const& mat);
	//Cone(glm::vec3 const& center, gfloat radius, float height, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m);

	glm::vec3 const& get_center() const;
	float const& get_radius() const;
	
	glm::vec3 const& get_center2() const; //Spitze
	
	bool intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const;

	/*virtual*/ std::ostream& print(std::ostream& os) const;

private:
	glm::vec3 center_;
	float radius_;
	glm::vec3 center2_;
};

#endif // #ifndef BUW_CONE_HPP