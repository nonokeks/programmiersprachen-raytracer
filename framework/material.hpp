#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP value
#include <iostream>
#include <string>
#include "color.hpp"

class Material
{
public:
	Material();
	Material(std::string name, Color const& ka, Color const& kd, Color const& ks, float m);
	~Material();
//getter
	std::string const& get_name()const;
	Color const& get_ka() const;
	Color const& get_kd() const;
	Color const& get_ks() const;
	float get_m() const;

//operator<<
	friend std::ostream& operator<<(std::ostream& os, Material const& mat);
//Shape ändern


private:
	std::string name_;
	Color ka_;
	Color kd_;
	Color ks_;
	float m_;



};


#endif