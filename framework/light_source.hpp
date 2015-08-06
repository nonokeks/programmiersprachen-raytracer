#ifndef BUW_LIGHT_SOURCES_HPP
#define BUW_LIGHT_SOURCES_HPP 
#include <glm/vec3.hpp>
#include <string>

class Light_sources
{
public:
	Light_sources(std::string name, glm::vec3 const& pos, float ambient, float diffuse);
	Light_sources();
	~Light_sources();

private:
	std::string name_;
	glm::vec3 pos_; //Position
	float la_; //ambienter Anteil
	float ld_; //diffuser Anteil
	
};

#endif