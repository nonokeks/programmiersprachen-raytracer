#include "box.hpp"

Box::Box():
	Shape{},
	min_{0.0f, 0.0f, 0.0f},
	max_{0.0f, 0.0f, 0.0f} {}
	
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
	Shape{},
	min_{min},
	max_{max} {}
	
Box::Box(std::string name, glm::vec3 const& min, glm::vec3 const& max,
         std::string material):
	Shape{name, material}, 
	min_{min},
	max_{max} {}

glm::vec3 const& Box::get_min()const{
	return min_;
}
glm::vec3 const& Box::get_max()const{
	return max_;
}

std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
	os << "Min: " << min_.x << " " << min_.y << " " << min_.z << ", Max: " << 
       max_.x << " " << max_.y << " " << max_.z;
	return os;
}

/*
calculates possible intersection points of ray and box using slabs, 
chooses one and then calculates the normal at that point
*/
bool Box::intersect(Ray const& ray, float& distance, glm::vec3& intersection, 
    glm::vec3& normal) const
{
    double a = (min_.x - ray.origin.x) * ray.inv_direction.x;
    double b = (max_.x - ray.origin.x) * ray.inv_direction.x;
    double tmin = std::min(a, b);
    double tmax = std::max(a, b);

    a = (min_.y - ray.origin.y) * ray.inv_direction.y;
    b = (max_.y - ray.origin.y) * ray.inv_direction.y;
    tmin = std::max(tmin, std::min(a, b));
    tmax = std::min(tmax, std::max(a, b));

    a = (min_.z - ray.origin.z) * ray.inv_direction.z;
    b = (max_.z - ray.origin.z) * ray.inv_direction.z;
    tmin = std::max(tmin, std::min(a, b));
    tmax = std::min(tmax, std::max(a, b));

    float t = tmin;
    if (t < 0)
    {
    	t = tmax;
    	if (t < 0) return false;
    }
    
    intersection = ray.origin + ray.direction * t;
  
    // One value of the intersection has to be the same as max or min
    if (min_.x == intersection.x){
        //front: 
        normal = generate_normale(glm::vec3(min_.x, max_.y, max_.z));
    }
    else if (max_.x == intersection.x){
        // back:
        normal = generate_normale(glm::vec3(max_.x, min_.y, min_.z));
    }
    else if (min_.y == intersection.y){
        //left side:
        normal = generate_normale(glm::vec3(max_.x, min_.y, max_.z));
    }
    else if (max_.y == intersection.y){
        //right side:
        normal = generate_normale(glm::vec3(min_.x, max_.y, min_.z) );
    }
    else if (min_.z == intersection.z){
        //bottom: 
        normal = generate_normale(glm::vec3(max_.x, max_.y, min_.z));
    }
    else if (max_.z == intersection.z){
        //top: 
        normal = generate_normale(glm::vec3(min_.x, min_.y, max_.z));
    }
    
    if (tmax > std::max(0.0, tmin)) {
        distance = sqrt(tmin * tmin * (ray.direction.x * ray.direction.x +
                        ray.direction.y * ray.direction.y + ray.direction.z * 
                        ray.direction.z));
        return true;
    }
    return false;
}


glm::vec3 Box::generate_normale(glm::vec3 const& p1, glm::vec3 const& p2, 
    glm::vec3 const& p3)const
{
    glm::vec3 normale(0.0,0.0,0.0);

    // is a plane possible?
    float rx = (p3.x-p1.x)/(p2.x-p1.x);
    float ry = (p3.y-p1.y)/(p2.y-p1.y);
    float rz = (p3.z-p3.z)/(p2.z-p1.z);

    if(rx == ry && ry == rz){
        // calculate normal of the line (direction vector * normal vector = 0)
        normale.x = (p2.y-p1.y) * -1;
        normale.y = (p2.x-p1.x);
    }
    else{
        // Cross product of both direction vectors
        normale.x = ((p2.y-p1.y) * (p3.z-p1.z)) - ((p2.z-p1.z) * (p3.y-p1.y));
        normale.y = ((p2.z-p1.z) * (p3.x-p1.x)) - ((p2.x-p1.x) * (p3.z-p1.z));
        normale.z = ((p2.x-p1.x) * (p3.y-p1.y)) - ((p2.y-p1.y) * (p3.x-p1.x));
    }
    
	normale = glm::normalize(normale);
    return normale;
}

glm::vec3 Box::generate_normale(glm::vec3 const& v)const{
    glm::vec3 normale(0.0,0.0,0.0);

    if (max_.x - v.x > 0){
        normale.x = 1; 
    }
    else if (max_.x - v.x < 0){
        normale.x = -1;
    }

    if (max_.y - v.y > 0){
        normale.y = 1; 
    }
    else if (max_.y - v.y < 0){
        normale.y = -1;
    }

    if (max_.z - v.z > 0){
		normale.z = 1; 
    }
    else if (max_.z - v.z < 0){
        normale.z = -1;
    }

    return normale;
}