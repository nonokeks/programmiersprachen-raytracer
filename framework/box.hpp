#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape
{
public:
	Box();
	Box(glm::vec3 min, glm::vec3 max);
	~Box();

	glm::vec3 get_min()const;
	glm::vec3 get_max()const;

	/*virtual*/ float area() const;
	/*virtual*/ float volume() const;

private:
	glm::vec3 min_;
	glm::vec3 max_;
};


#endif //  #ifndef BUW_BOX_HPP