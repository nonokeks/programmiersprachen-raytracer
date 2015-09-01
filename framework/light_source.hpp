#ifndef BUW_LIGHT_SOURCES_HPP
#define BUW_LIGHT_SOURCES_HPP 

#include <glm/vec3.hpp>
#include <string>

#include "color.hpp"

class Light_source{
	public:
		Light_source(std::string name, glm::vec3 const& pos, Color const& ambient, Color const& diffuse);
		Light_source();
		//~Light_source(); Wieso gibt es den nicht??

		std::string get_name() const;
		glm::vec3 const& get_position() const;
		Color const& get_ambiente() const; 
		Color const& get_diffuse() const;

	private:
		std::string name_;
		glm::vec3 pos_; // Position
		Color la_; // ambient portion
		Color ld_; // diffuse portion
	
};

#endif
