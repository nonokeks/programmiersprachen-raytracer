#include <composite.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <triangle.hpp>
#include <shape.hpp>

Composite::Composite() :
	Shape{{{INFINITY,INFINITY,INFINITY},{-INFINITY,-INFINITY,-INFINITY}}},
	shapes_{}
{}


Composite::Composite(std::string const& name) :
	Shape{Material{}, name, {{INFINITY,INFINITY,INFINITY},{-INFINITY,-INFINITY,-INFINITY}}},
	shapes_{}
{}