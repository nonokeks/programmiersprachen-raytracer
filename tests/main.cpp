#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include "sphere.hpp"
#include "box.hpp"
#include "color.hpp"
#include <iostream>
#include <string>

//6.2
TEST_CASE("sphere_with_radius_2", "[sphere1]"){
	glm::vec3 vec{1.0f,2.0f,0.0f};
	Sphere s1{vec , 2.0f};
	REQUIRE(s1.volume() == Approx(33.51));
	REQUIRE(s1.area() == Approx(50.265));
	REQUIRE(s1.get_center() == vec);
	REQUIRE(s1.get_radius() == 2.0f);
}
TEST_CASE("sphere_default_constructor", "[sphere2]"){
	Sphere s1{};
	glm::vec3 vec{0.0f,0.0f,0.0f};
	REQUIRE(s1.volume() == 0);
	REQUIRE(s1.area() == 0);
	REQUIRE(s1.get_center() == vec);
	REQUIRE(s1.get_radius() == 0);
}
TEST_CASE("box_default", "[box1]"){
	glm::vec3 vec{0.0f,0.0f,0.0f};
	Box b1{};
	REQUIRE(b1.volume() == 0);
	REQUIRE(b1.area() == 0);
	REQUIRE(b1.get_max() == vec);
	REQUIRE(b1.get_min() == vec);
}
TEST_CASE("box", "[box2]"){
	glm::vec3 vec1{0.0f,0.0f,0.0f};
	glm::vec3 vec2{2.0f,1.0f,3.0f};
	Box b1{vec2, vec1};
	REQUIRE(b1.volume() == Approx(6));
	REQUIRE(b1.area() == Approx(22));
	REQUIRE(b1.get_max() == vec1);
	REQUIRE(b1.get_min() == vec2);
}

//6.3
TEST_CASE("box_with_color", "[color_and_name1]"){
	glm::vec3 vec1{0.0f,0.0f,0.0f};
	glm::vec3 vec2{2.0f,1.0f,3.0f};
	Color c{1.0f, 0.5f, 0.2f};
	std::string name = "box";
	Box b1{vec2, vec1, name, c};
	REQUIRE(b1.get_color().r == c.r);
	REQUIRE(b1.get_color().g == c.g);
	REQUIRE(b1.get_color().b == c.b);
	REQUIRE(b1.get_name() == name);
}
TEST_CASE("sphere_with_color", "[color_and_name2]"){
	glm::vec3 vec1{0.0f,0.0f,0.0f};
	Color c{1.0f, 0.5f, 0.2f};
	std::string name = "box";
	Sphere s1{vec1 , 2.0f, name, c};
	REQUIRE(s1.get_color().r == c.r);
	REQUIRE(s1.get_color().g == c.g);
	REQUIRE(s1.get_color().b == c.b);
	REQUIRE(s1.get_name() == name);
}




int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
