#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP
#include <shape.hpp>
#include <memory>
#include <map>
#include <sphere.hpp>
#include <box.hpp>
#include <triangle.hpp>



class Composite : public Shape {
public:
	Composite();
	Composite(std::string const& name);
	
	~Composition();
	
	void add(std::shared_ptr<Shape>& shape);
	void remove(std::string const& name);
	
	std::ostream& print(std::ostream& os) const override;
	
	std::map<std::string, std::shared_ptr<Shape>> get_children();
	
private:
	std::map<std::string,std::shared_ptr<Shape>> shapes_;
};

#endif