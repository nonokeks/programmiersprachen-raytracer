#include <composite.hpp>

Composite::Composite() :
	Shape{}{}

Composite::Composite(std::string const& name) :
	Shape{name, ""}{}

Composite::~Composite(){}

void Composite::add(std::shared_ptr<Shape>& shape) {
	shapes_.insert(shapes_.begin(),std::pair<std::string,std::shared_ptr<Shape>>(shape->get_name(),shape));
}

void Composite::remove(std::string const& name) {
	shapes_.erase(name);
}

std::ostream& Composite::print(std::ostream& os) const {
	for(auto element: shapes_) {
		element.second->print(os);
	}
	return os;
}

std::map<std::string, std::shared_ptr<Shape>> Composite::get_children() {
	return shapes_;
}