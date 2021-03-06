#include "light_source.hpp"

Light_source::Light_source(std::string name, glm::vec3 const& pos, 
                           Color const& ambient, Color const& diffuse):
	name_{name},
    pos_{pos},
    la_{ambient},
    ld_{diffuse}{}

Light_source::Light_source():
    name_{""},
    pos_{0.0,0.0,0.0},
    la_{},
    ld_{}{}

Light_source::~Light_source(){}

std::string Light_source::get_name() const{
	return name_;
}
glm::vec3 const& Light_source::get_position() const{
	return pos_;
}
Color const& Light_source::get_ambiente() const{
	return la_;
} 
Color const& Light_source::get_diffuse() const{
	return ld_;
}
