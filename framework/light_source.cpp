#include "light_sources.hpp"
#include <glm/vec3.hpp>
#include <string>

Light_sources::Light_sources(std::string name, glm::vec3 pos, float ambient, float diffuse): name_{name},
pos_{pos}, la_{ambient}, ld_{diffuse}{}
Light_sources::Light_sources(): name_{""}, pos_{0.0,0.0,0.0}, la_{0.0f}, ld_{0.0}{}
Light_sources::~Light_sources();