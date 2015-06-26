#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#include <iostream>
#include <string>
#include "color.hpp"

class Shape
{
public:
	Shape(): name_{""}, color_{0.0f, 0.0f, 0.0f}{}
	Shape(std::string name, Color color): name_{name}, color_{color} {}

	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const{
		os << "Name: " << name_ << ", Color: " << color_.r << " " << color_.g << " " << color_.b << "\n";
		return os;
	}

	std::string get_name()const{
		return name_;
	}
	Color get_color() const{
		return color_;
	}

	friend std::ostream& operator<<(std::ostream& os, Shape const& s){
		return s.print(os);
	}


private:
	std::string name_;
	Color color_;
};


#endif // #ifndef BUW_SHAPE_HPP