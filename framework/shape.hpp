#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#include <iostream>
#include <string>
#include "color.hpp"
#include "ray.hpp"

class Shape
{
public:
	Shape(): name_{""}, color_{0.0f, 0.0f, 0.0f}{}
	Shape(std::string name, Color const& color): name_{name}, color_{color} {}
	//virtual ~Shape(){std::cout << "Shape Destructor" << std::endl;}
	//~Shape(){std::cout << "Shape Destructor" << std::endl;}

	//Shape(): name_{""}, material{}{}
	//Shape(std::string name, Material const& mat): name_{name}, material_{mat} {}
	//Shape(std::string name, std::string name_mat, Color const& ka, Color const& kd, Color const& ks, float m): name_{name}, 
	//material_{name_mat, ka, kd, ks, m} {}

	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const{
		os << "Name: " << name_ << ", Color: " << color_.r << " " << color_.g << " " << color_.b << "\n";
		return os;
	}

	std::string const& get_name()const{
		return name_;
	}
	Color const& get_color() const{
		return color_;
	}

	friend std::ostream& operator<<(std::ostream& os, Shape const& s){
		return s.print(os);
	}

	virtual bool intersect(Ray const& ray, float& distance) const = 0;

private:
	std::string name_;
	Color color_;
	// Material material_;
};


#endif // #ifndef BUW_SHAPE_HPP