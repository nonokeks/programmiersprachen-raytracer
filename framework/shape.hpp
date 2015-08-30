#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"

class Shape
{
public:
	/*
	Shape(): name_{""}, color_{0.0f, 0.0f, 0.0f}{}
	Shape(std::string name, Color const& color): name_{name}, color_{color} {}
	virtual ~Shape(){std::cout << "Shape Destructor" << std::endl;}
	~Shape(){std::cout << "Shape Destructor" << std::endl;}

	Shape(): name_{""}, material_{}{}
	Shape(std::string name, Material const& mat): name_{name}, material_{mat} {}
	Shape(std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m): name_{name}, 
	material_{name_mat, ka, kd, ks, m} {}*/

	Shape(): name_{""}, matname_{""}{}
	Shape(std::string name, std::string material): name_{name}, matname_{material} {}
	


	virtual std::ostream& print(std::ostream& os) const{
		os << "Name: " << name_ << " Material: " << matname_ << std::endl;;
		return os;
	}

	std::string const& get_name()const{
		return name_;
	}
	
	std::string const& get_material()const{
		return matname_;
	}
	/*Material const& get_material() const{
		return material_;
	}*/
	
	
	
	//Ausgangsgleichung: ax^2 + bx + c = 0
	bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1){ //x0, x1 geben t0,t1 Auftreffpunkte
		float discr = b * b - 4 * a * c;
		if (discr < 0){
			return false;
		}
		else if (discr == 0) {
		x0 = - 0.5 * b / a;
		x1 = - 0.5 * b / a;
		}
		else {
			float q = (b > 0) ?
				-0.5 * (b + sqrt(discr)) :
				-0.5 * (b - sqrt(discr));
			x0 = q / a;
			x1 = c / q;
		}
		if (x0 > x1) {
			std::swap(x0, x1);
		}
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os, Shape const& s){
		return s.print(os);
	}

	virtual bool intersect(Ray const& ray, float& distance) const = 0;
	virtual bool intersect(Ray const& ray, float& distance, glm::vec3& intersection,
	glm::vec3& normal) const = 0;

private:
	std::string name_;
	//Color color_;
	//Material material_;
	std::string matname_;
};


#endif // #ifndef BUW_SHAPE_HPP
