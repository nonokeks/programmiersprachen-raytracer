#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP value // was hat das hier zu tun??

#include <iostream>
#include <string>

#include "color.hpp"

class Material{
	public:
		Material();
		Material(std::string name, Color const& ka, Color const& kd, 
			     Color const& ks, float m, float refract, float opacity);
		~Material();
		
		std::string const& get_name()const;
		Color const& get_ka() const;
		Color const& get_kd() const;
		Color const& get_ks() const;
		float get_m() const;
		float get_refract() const; 
		float get_opacity() const; 

		friend std::ostream& operator<<(std::ostream& os, 
			Material const& mat);

	private:
		std::string name_;
		Color ka_;
		Color kd_;
		Color ks_;
		float m_; // mirror

		float refract_; // Refractive index
		float opacity_; // Transparency

};


#endif
