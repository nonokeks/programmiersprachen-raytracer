#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include "sphere.hpp"

TEST_CASE("sphere", "[sphere]"){
	glm::vec3 vec{0.0f,0.0f,0.0f};
	Sphere s1{vec , 2.0f};
	REQUIRE(s1.volume() == Approx(33.51));
	REQUIRE(s1.area() == Approx(50.265));./
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
