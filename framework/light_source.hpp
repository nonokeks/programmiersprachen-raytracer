#ifndef BUW_LIGHT_SOURCES_HPP
#define BUW_LIGHT_SOURCES_HPP 
#include <glm/vec3.hpp>
#include <string>

class Light_source
{
public:
	Light_source(std::string name, glm::vec3 const& pos, float ambient, float diffuse);
	Light_source();
	~Light_source();

private:
	std::string name_;
	glm::vec3 pos_; //Position
	float la_; //ambienter Anteil
	float ld_; //diffuser Anteil
	
};

#endif