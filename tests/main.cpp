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

/*
TEST_CASE("material", "[mat]"){
	std::map<std::string, Material> mat;

	Sdf_loader s{};
	s.load_material("./mat.txt", mat);


	for(std::map<std::string, Material>::iterator it = mat.begin();
	 it != mat.end(); ++it){
	 	std::cout << it->second << std::endl;
	}
}*/

/*
TEST_CASE("camera", "[cam]"){
	Camera c1{"cam", 22.3f};
	std::string s = "cam";
	REQUIRE(s.compare(c1.get_name()) == 0);
	REQUIRE(c1.get_angle() == Approx(22.3));

	Camera c2{};
	REQUIRE(c2.get_name().compare("") == 0);
	REQUIRE(c2.get_angle() == Approx(0.0));
}*/

/*
NEU - Light_source - Color
TEST_CASE("lights", "[light]"){
	glm::vec3 vec1{-1.0f,-1.0f,-1.0f};
	Light_source l{"light", vec1, 2.0f, 1.0f};
	REQUIRE(l.get_name().compare("light") == 0);
	REQUIRE(l.get_position() == vec1);
	

	glm::vec3 vec2{0.0,0.0,0.0};
	Light_source l2{};
	REQUIRE(l2.get_name().compare("") == 0);
	REQUIRE(l2.get_position() == vec2);
	
}*/

/*
TEST_CASE("scene", "[scene]"){
	Color red{1.0,0.0,0.0};
	Camera cam{"cam", 22.3f};
	Renderer_data render{800,600, "cam", "notyet.txt"};
	Scene s{red, cam, render};
	REQUIRE(s.cam.get_name() == cam.get_name());
	REQUIRE(s.cam.get_angle() == cam.get_angle());
	REQUIRE(s.ambient == red);
	REQUIRE(s.render.height == render.height);
	REQUIRE(s.render.width == render.width);
	REQUIRE(s.render.filename == render.filename);
	
	Scene s2{};
	Color farb{};
	Camera cam2{};
	Renderer_data render2{};
	REQUIRE(s2.cam.get_name() == cam2.get_name());
	REQUIRE(s2.cam.get_angle() == cam2.get_angle());
	REQUIRE(s2.ambient == farb);
	REQUIRE(s2.render.height == render2.height);
	REQUIRE(s2.render.width == render2.width);
	REQUIRE(s2.render.filename == render2.filename);
}*/

/*

TEST_CASE("Sdf_loader_material", "[sdf_loader]"){
	
	Sdf_loader loader{"./materials.txt"};
	Scene s = loader.load_scene("./materials.txt");

	for(std::map<std::string, Material>::iterator it = s.material.begin();
	 it != s.material.end(); ++it){
	 	std::cout << it->second << std::endl;
	}

}

TEST_CASE("Sdf_loader_lights", "[sdf_loader]"){
	
	Sdf_loader loader{"./lights.txt"};
	Scene s = loader.load_scene("./lights.txt");

	for(std::vector<Light_source>::iterator it = s.lights.begin();
	 it != s.lights.end(); ++it){
		Light_source i = *it;
	 	std::cout << i.get_name() << " " ;
	 	std::cout << i.get_position().x << " " << i.get_position().y << " ";
	 	std::cout << i.get_position().z;
	 	std::cout << " " << i.get_ambiente() << " " << i.get_diffuse() << "\n";
	}

}


TEST_CASE("Sdf_loader_shapes", "[sdf_loader]"){
	
	Sdf_loader loader{"./geometry.txt"};
	Scene s = loader.load_scene("./geometry.txt");

	
	//std::vector<std::shared_ptr <Shape>> shapes

	for(std::vector<std::shared_ptr <Shape>>::iterator it = s.shapes.begin();
	 it != s.shapes.end(); ++it){
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

/*
TEST_CASE("Sdf_loader_complete", "[sdf_loader]"){
	
	Sdf_loader loader{"./test.txt"};
	Scene s;
	s = loader.load_scene("./test.txt");
	std::cout << std::endl;

	for(std::vector<std::shared_ptr <Shape>>::iterator it = s.shapes.begin();
	 it != s.shapes.end(); ++it){
	 	std::cout << **it << std::endl;
	}
	for(std::vector<Light_source>::iterator it = s.lights.begin();
	 it != s.lights.end(); ++it){
		Light_source i = *it;
	 	std::cout << i.get_name() << " " ;
<<<<<<< HEAD
	 	std::cout << i.get_position().x << " " << i.get_position().y << " " ;
	 	std::cout << i.get_position().z;
	 	std::cout << " " << i.get_ambiente() << " " << i.get_diffuse() << "\n";
=======
	 	std::cout << i.get_position().x << " " << i.get_position().y << " " << i.get_position().z;
	 	std::cout << " " << i.get_ambiente() << " " << i.get_diffuse() << std::endl;
>>>>>>> master
	}
	for(std::map<std::string, Material>::iterator it = s.material.begin();
	 it != s.material.end(); ++it){
	 	std::cout << it->second << std::endl;
	}
	std::cout << s.cam.get_name() << " " << s.cam.get_angle() << std::endl;
	std::cout << s.render.filename << " " << s.render.width << " " ;
	std::cout << s.render.height << std::endl;
	std::cout << "Ambient: " << s.ambient << std::endl;
}*/


TEST_CASE("Render_test1", "[renderer]"){
	
	Renderer r;

	r.render_scene("./test_neu01.txt"); 

	Scene s = r.get_scene();

	std::cout << std::endl;

	
	for(std::map<std::string, Material>::const_iterator it= s.material.begin();
	 it != s.material.end(); ++it){
	 	std::cout << it->second << std::endl;
	}

	/*
	for(std::vector<std::shared_ptr <Shape>>::iterator it = s.shapes.begin();
	 it != s.shapes.end(); ++it){
	 	std::cout << **it << std::endl;
	}*/
	
	
	for(std::vector<Light_source>::const_iterator it = s.lights.begin();
	 it != s.lights.end(); ++it){
		Light_source i = *it;
	 	std::cout << i.get_name() << " " ;
	 	std::cout << i.get_position().x << " " << i.get_position().y << " ";
	 	std::cout << i.get_position().z << std::cout << " " 
		<< i.get_ambiente();
	 	std::cout << " " << i.get_diffuse() << std::endl;
	}
	
	std::cout << s.cam.get_name() << " " << s.cam.get_angle() << std::endl;
	std::cout << "pos " << s.cam.get_position().x << " " <<
	 s.cam.get_position().y << " " << s.cam.get_position().z << " "
	<< s.cam.get_direction().x << " " << s.cam.get_direction().y << " " 
	<< s.cam.get_direction().z << std::endl;
	std::cout << s.render.camera_name << " " << s.render.filename << " " 
	<< s.render.width << " " << s.render.height << std::endl;
	std::cout << "Ambient: " << s.ambient << std::endl;
	/*
	std::vector<Ray> rays;
	s.cam.generate_rays(r.get_width(), r.get_height() , rays);

	for (std::vector<Ray>::iterator i = rays.begin(); i < rays.end(); ++i)
  	{
    	Optional_hit o = r.intersect(*i);
        if (o.hit)
        {
            std::cout << o.distance << " " << o.shape->get_name() << std::endl;
        } 
  	}*/

	
}





int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
