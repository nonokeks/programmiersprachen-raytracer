#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "light_source.hpp"
#include "renderer.hpp"
#include <iostream>
#include <string>
#include <map>
#include "sdf_loader.hpp"
#include "material.hpp"
using namespace std;

// //6.2
// TEST_CASE("sphere_with_radius_2", "[sphere1]"){
// 	glm::vec3 vec{1.0f,2.0f,0.0f};
// 	Sphere s1{vec , 2.0f};
// 	REQUIRE(s1.volume() == Approx(33.51));
// 	REQUIRE(s1.area() == Approx(50.265));
// 	REQUIRE(s1.get_center() == vec);
// 	REQUIRE(s1.get_radius() == 2.0f);
// }
// TEST_CASE("sphere_default_constructor", "[sphere2]"){
// 	Sphere s1{};
// 	glm::vec3 vec{0.0f,0.0f,0.0f};
// 	REQUIRE(s1.volume() == 0);
// 	REQUIRE(s1.area() == 0);
// 	REQUIRE(s1.get_center() == vec);
// 	REQUIRE(s1.get_radius() == 0);
// }
// TEST_CASE("box_default", "[box1]"){
// 	glm::vec3 vec{0.0f,0.0f,0.0f};
// 	Box b1{};
// 	REQUIRE(b1.volume() == 0);
// 	REQUIRE(b1.area() == 0);
// 	REQUIRE(b1.get_max() == vec);
// 	REQUIRE(b1.get_min() == vec);
// }
// TEST_CASE("box", "[box2]"){
// 	glm::vec3 vec1{0.0f,0.0f,0.0f};
// 	glm::vec3 vec2{2.0f,1.0f,3.0f};
// 	Box b1{vec2, vec1};
// 	REQUIRE(b1.volume() == Approx(6));
// 	REQUIRE(b1.area() == Approx(22));
// 	REQUIRE(b1.get_max() == vec1);
// 	REQUIRE(b1.get_min() == vec2);
// }

// //6.3
// TEST_CASE("box_with_color", "[color_and_name1]"){
// 	glm::vec3 vec1{0.0f,0.0f,0.0f};
// 	glm::vec3 vec2{2.0f,1.0f,3.0f};
// 	Color c{1.0f, 0.5f, 0.2f};
// 	std::string name = ("box");
// 	Box b1{vec2, vec1, name, c};
// 	REQUIRE(b1.get_color().r == c.r);
// 	REQUIRE(b1.get_color().g == c.g);
// 	REQUIRE(b1.get_color().b == c.b);
// 	REQUIRE(b1.get_name().compare("box") == 0);
// }
// TEST_CASE("sphere_with_color", "[color_and_name2]"){
// 	glm::vec3 vec1{0.0f,0.0f,0.0f};
// 	Color c{1.0f, 0.5f, 0.2f};
// 	std::string name = ("sphere");
// 	Sphere s1{vec1 , 2.0f, name, c};
// 	REQUIRE(s1.get_color().r == c.r);
// 	REQUIRE(s1.get_color().g == c.g);
// 	REQUIRE(s1.get_color().b == c.b);
// 	REQUIRE(s1.get_name().compare(name) == 0);
// }

// //6.5
// TEST_CASE("print_sphere", "[print1]"){
// 	glm::vec3 vec{1.0f,2.0f,0.0f};
// 	Color c{1.0f, 0.5f, 0.2f};
// 	std::string name = ("sphere");
// 	Sphere s1{vec , 2.0f, name, c};
// 	std::cout << s1 << std::endl;
// }
// TEST_CASE("print_box", "[print2]"){
// 	glm::vec3 vec1{0.0f,0.0f,0.0f};
// 	glm::vec3 vec2{2.0f,1.0f,3.0f};
// 	Color c{1.0f, 0.2f, 0.7f};
// 	std::string name = ("box");
// 	Box b1{vec2, vec1, name, c};
// 	std::cout << b1 << std::endl;
// }

// //6.6
// TEST_CASE("intersectRaySphere", "[intersect]"){
// 	//Ray
// 	glm::vec3 ray_origin(0.0,0.0,0.0);
// 	//v = glm::normalize(some_vector);
// 	glm::vec3 ray_direction(0.0,0.0,1.0);

// 	//Sphere
// 	glm::vec3 sphere_center(0.0,0.0,5.0);
// 	float sphere_radius(1.0);

// 	float distance(0.0);
// 	auto result = glm::intersectRaySphere(ray_origin, ray_direction, sphere_center, sphere_radius* sphere_radius, distance);
// 	REQUIRE(distance == Approx(4.0));
// }
// TEST_CASE("intersect_sphere_ray", "[intersect_sphere]"){
// 	glm::vec3 origin(0.0,0.0,0.0);
// 	glm::vec3 direction(0.0,0.0,1.0);
// 	Ray r{origin, direction};

// 	glm::vec3 vec(0.0,0.0,5.0);
// 	Sphere s1{vec , 1.0};
// 	float distance(0.0);
// 	s1.intersect(r, distance);
// 	REQUIRE(distance == Approx(4.0));
// }
// TEST_CASE("intersect_sphere_ray2", "[intersect_sphere2]"){
// 	glm::vec3 origin(0.0,0.0,0.0);
// 	glm::vec3 direction(0.0,0.0,2.0);
// 	Ray r{origin, direction};

// 	glm::vec3 vec(0.0,0.0,4.0);
// 	Sphere s1{vec , 1.0};
// 	float distance(0.0);
// 	bool b = s1.intersect(r, distance);
// 	REQUIRE(distance == Approx(3.0));
// 	REQUIRE(b);
// }

// //6.8
// TEST_CASE("virtual_destructor", "[destructor]"){
// 	Color red(255, 0, 0);
// 	glm::vec3 position(0,0,0);
// 	Sphere* s1 = new Sphere(position, 1.2, "sphere0", red);
// 	Shape* s2 = new Sphere(position, 1.2, "sphere1", red);

// 	s1->print(std::cout);
// 	std::cout << "\n";
// 	s2->print(std::cout);

// 	delete s1;
// 	delete s2;
// }


//7
TEST_CASE("box_intersect", "[intersect_box]"){
	glm::vec3 vec1{0.0f,0.0f,0.0f};
	glm::vec3 vec2{1.0f,1.0f,1.0f};
	Box b1{vec1, vec2};

	glm::vec3 origin(-1.0,0.0,0.0);
	glm::vec3 direction(1.0,0.5,0.0);
	Ray r{origin, direction};
	float distance(0.0);
	REQUIRE(b1.intersect(r, distance));
	std::cout <<"\n" << distance << std::endl;
}
TEST_CASE("box_intersect2", "[intersect_box2]"){
	glm::vec3 vec1{0.0f,0.0f,0.0f};
	glm::vec3 vec2{1.0f,1.0f,1.0f};
	Box b1{vec1, vec2};

	glm::vec3 origin(12.0,0.5,0.5);
	glm::vec3 direction(1.0,0.0,0.0);
	Ray r{origin, direction};
	float distance(0.0);
	REQUIRE(b1.intersect(r, distance)==false);
	std::cout <<"\n" << distance << std::endl;
}
TEST_CASE("box_intersect3", "[intersect_box3]"){
	glm::vec3 vec1{-1.0f,-1.0f,-1.0f};
	glm::vec3 vec2{3.0f,3.0f,3.0f};
	Box b1{vec1, vec2};

	glm::vec3 origin(-12.0,0.5,0.5);
	glm::vec3 direction(1.0,0.0,0.0);
	Ray r{origin, direction};
	float distance(0.0);
	REQUIRE(b1.intersect(r, distance));
	std::cout <<"\n" << distance << std::endl;
}

/*
TEST_CASE("material", "[mat]"){
	std::map<std::string, Material> mat;

	Sdf_loader s{};
	s.load_material("./mat.txt", mat);


	for(std::map<std::string, Material>::iterator it = mat.begin(); it != mat.end(); ++it){
	 	std::cout << it->second << std::endl;
	}
}*/


TEST_CASE("camera", "[cam]"){
	Camera c1{"cam", 22.3f};
	std::string s = "cam";
	REQUIRE(s.compare(c1.get_name()) == 0);
	REQUIRE(c1.get_angle() == Approx(22.3));

	Camera c2{};
	REQUIRE(c2.get_name().compare("") == 0);
	REQUIRE(c2.get_angle() == Approx(0.0));
}

TEST_CASE("lights", "[light]"){
	glm::vec3 vec1{-1.0f,-1.0f,-1.0f};
	Light_source l{"light", vec1, 2.0f, 1.0f};
	REQUIRE(l.get_name().compare("light") == 0);
	REQUIRE(l.get_position() == vec1);
	REQUIRE(l.get_ambiente() == Approx(2.0));
	REQUIRE(l.get_diffuse() == Approx(1.0));

	glm::vec3 vec2{0.0,0.0,0.0};
	Light_source l2{};
	REQUIRE(l2.get_name().compare("") == 0);
	REQUIRE(l2.get_position() == vec2);
	REQUIRE(l2.get_ambiente() == Approx(0.0));
	REQUIRE(l2.get_diffuse() == Approx(0.0));
}


TEST_CASE("scene", "[scene]"){
	Color red{1.0,0.0,0.0};
	Camera cam{"cam", 22.3f};
	Renderer render{800,600,"notyet.txt"};
	Scene s{red, cam, render};
	REQUIRE(s.cam.get_name() == cam.get_name());
	REQUIRE(s.cam.get_angle() == cam.get_angle());
	REQUIRE(s.ambient == red);
	REQUIRE(s.render.get_height() == render.get_height());
	REQUIRE(s.render.get_width() == render.get_width());
	REQUIRE(s.render.get_filename() == render.get_filename());
	
	Scene s2{};
	Color farb{};
	Camera cam2{};
	Renderer render2{};
	REQUIRE(s2.cam.get_name() == cam2.get_name());
	REQUIRE(s2.cam.get_angle() == cam2.get_angle());
	REQUIRE(s2.ambient == farb);
	REQUIRE(s2.render.get_height() == render2.get_height());
	REQUIRE(s2.render.get_width() == render2.get_width());
	REQUIRE(s2.render.get_filename() == render2.get_filename());
}

/*

TEST_CASE("Sdf_loader_material", "[sdf_loader]"){
	
	Sdf_loader loader{"./materials.txt"};
	Scene s = loader.load_scene("./materials.txt");

	for(std::map<std::string, Material>::iterator it = s.material.begin(); it != s.material.end(); ++it){
	 	std::cout << it->second << std::endl;
	}

}

TEST_CASE("Sdf_loader_lights", "[sdf_loader]"){
	
	Sdf_loader loader{"./lights.txt"};
	Scene s = loader.load_scene("./lights.txt");

	for(std::vector<Light_source>::iterator it = s.lights.begin(); it != s.lights.end(); ++it){
		Light_source i = *it;
	 	std::cout << i.get_name() << " " ;
	 	std::cout << i.get_position().x << " " << i.get_position().y << " " << i.get_position().z;
	 	std::cout << " " << i.get_ambiente() << " " << i.get_diffuse() << std::endl;
	}

}


TEST_CASE("Sdf_loader_shapes", "[sdf_loader]"){
	
	Sdf_loader loader{"./geometry.txt"};
	Scene s = loader.load_scene("./geometry.txt");

	
	//std::vector<std::shared_ptr <Shape>> shapes

	for(std::vector<std::shared_ptr <Shape>>::iterator it = s.shapes.begin(); it != s.shapes.end(); ++it){
	 	std::cout << **it << std::endl;
	}
}
TEST_CASE("Sdf_loader_camera", "[sdf_loader]"){
	
	Sdf_loader loader{"./camera.txt"};
	Scene s{};
	s = loader.load_scene("./camera.txt");

	
	std::cout << s.cam.get_name() << " " << s.cam.get_angle() << std::endl;
}
*/


TEST_CASE("Sdf_loader_complete", "[sdf_loader]"){
	
	Sdf_loader loader{"./test.txt"};
	Scene s = loader.load_scene("./test.txt");
	std::cout << std::endl;

	for(std::vector<std::shared_ptr <Shape>>::iterator it = s.shapes.begin(); it != s.shapes.end(); ++it){
	 	std::cout << **it << std::endl;
	}
	for(std::vector<Light_source>::iterator it = s.lights.begin(); it != s.lights.end(); ++it){
		Light_source i = *it;
	 	std::cout << i.get_name() << " " ;
	 	std::cout << i.get_position().x << " " << i.get_position().y << " " << i.get_position().z;
	 	std::cout << " " << i.get_ambiente() << " " << i.get_diffuse() << std::endl;
	}
	for(std::map<std::string, Material>::iterator it = s.material.begin(); it != s.material.end(); ++it){
	 	std::cout << it->second << std::endl;
	}
	std::cout << s.cam.get_name() << " " << s.cam.get_angle() << std::endl;
	std::cout << s.render.get_filename() << " " << s.render.get_width() << " " << s.render.get_height()  << std::endl;
	std::cout << "Ambient: " << s.ambient << std::endl;
}



int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
