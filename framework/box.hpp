#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include <cmath>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "color.hpp"
//#include "material.hpp"
#include "ray.hpp"
#include "shape.hpp"

//"" wenn vom Benutzer, <> wenn fertiger Header

class Box : public Shape {
	public:
		Box();
		Box(glm::vec3 const& min, glm::vec3 const& max);
		//delete?
		// Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color const& color);
		//~Box();
		//Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Material const& mat);
		//Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m);

		Box(std::string name,glm::vec3 const& min, glm::vec3 const& max, std::string material);

		glm::vec3 const& get_min()const;
		glm::vec3 const& get_max()const;

		/*virtual*/ std::ostream& print(std::ostream& os) const;

		//bool intersect(Ray const& ray, float& distance) const; //weg?
		bool intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal) const;
		glm::vec3 normale_box(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3)const;
		glm::vec3 normale_box(glm::vec3 const& v)const;

	private:
		glm::vec3 min_;
		glm::vec3 max_;

};

#endif //  #ifndef BUW_BOX_HPP
