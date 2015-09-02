// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

using namespace glm;

Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
	width_(w),
	height_(h),
	colorbuffer_(w*h, Color(0.0, 0.0, 0.0)),
	filename_(file),
	ppm_(width_, height_)
	{}

Renderer::Renderer():
	width_(0),
	height_(0),
	colorbuffer_(0, Color(0.0, 0.0, 0.0)),
	filename_(""),
	ppm_(width_, height_)
	{}

unsigned Renderer::get_width() const{
  return width_;
}
unsigned Renderer::get_height() const{
  return height_;
}
std::string Renderer::get_filename() const{
  return filename_;
}
Scene Renderer::get_scene() const{
  return scene_;
}

Renderer& Renderer::operator= (Renderer const& rhs){
  width_ = rhs.get_width();
  height_ = rhs.get_height();
  filename_ = rhs.get_filename();
  return *this;
}

void Renderer::render(){
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }
      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p){
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }
  ppm_.write(p);
}

Optional_hit Renderer::intersect(Ray const& ray) const{
  Optional_hit o;
  Optional_hit temp;
  std::vector<float> hits;  
  
 
  //for each composite
  for (std::vector<std::shared_ptr <Composite>>::const_iterator i =
      scene_.shape_composite.begin(); i != scene_.shape_composite.end(); ++i){
    //for each Shape in a composite
    std::map<std::string,std::shared_ptr<Shape>> temp_map = (**i).get_children();
	  for (std::map<std::string,std::shared_ptr<Shape>>::const_iterator it =
     temp_map.begin(); it != temp_map.end(); ++it){
      if (it == temp_map.begin() || !o.hit){
        o.hit = it->second->intersect(ray, o.distance, o.intersection, o.normal);
        o.shape = &*(it->second);
      }
      else {
        temp.hit = it->second->intersect(ray, temp.distance, temp.intersection,
                                         temp.normal);
        temp.shape = &*(it->second);
        if(o.distance > temp.distance && temp.distance > 0){
          o = temp;
        }
      }
    }
  }
  return o;
}

Color Renderer::raytrace(Ray const& ray, int depth){
  Optional_hit o = intersect(ray);
  if(o.hit) return shade(ray, o, depth);
  else return scene_.ambient;
}

Color Renderer::shade(Ray const& ray, Optional_hit const& o, int depth){
  Color color; // Ray color 
  Ray rRay, tRay, sRay; // Reflection-, Refraction- and Shadow rays 
  Color rColor, tColor; // Color of reflected and refracted ray 
  // Material of intersected Shape
  Material temp_mat = scene_.material[o.shape->get_material()]; 

  for (std::vector<Light_source>::const_iterator l = scene_.lights.begin();
       l != scene_.lights.end(); ++l)
  {
    sRay = Ray(o.intersection, glm::normalize((*l).get_position()));
    // Is the dot product of normal and sRay.direction positive?
    if(glm::dot(o.normal, sRay.direction) > 0){
      Optional_hit shadow= intersect(sRay);
      float shading = glm::dot(o.normal, glm::normalize((*l).get_position()));
      float shading_pos = std::max(shading, 0.0f);
      
      if (!shadow.hit)// not in shadow
      {
        color +=  (*l).get_diffuse() * (( temp_mat.get_kd() * shading_pos) +
                   temp_mat.get_ks());
      }
      else // its in the shadow
      {
        color +=  (*l).get_diffuse() * (( temp_mat.get_kd() * shading_pos));
      }
    }
  }
  
  if (depth <= 3){ //3 = Max depth
    if (temp_mat.get_m() != 0){ // Object reflects
      rRay.origin = o.intersection;
      // Reflection vector
      rRay.direction = glm::reflect(o.intersection, o.normal);
      // raytrace reflection ray
      rColor = raytrace(rRay, depth + 1);
      // scale Color
      rColor *= temp_mat.get_m();
      color += rColor; 
    } 
    
    if (temp_mat.get_opacity() != 0){ // Object transparent -> refraction
      // Ray in direction of refraction
      tRay.origin = o.intersection;
      tRay.direction = glm::refract(o.intersection, o.normal, 
                                    temp_mat.get_refract());

  		if(temp_mat.get_m() != 1) //object is not selfreflection complete
      {
  			tColor = raytrace(tRay, depth + 1);
  			tColor *= temp_mat.get_opacity();
  			color += tColor;
  		}
    }
  }
  // ambient lightning
  color += temp_mat.get_ka() * scene_.ambient;
  return color;
}

void Renderer::render_scene(std::string filename){
  // Load scene
  Sdf_loader loader{filename};
  scene_ = loader.load_scene(filename);

  // write data from transfer object into renderer
  width_ = scene_.render.width;
  height_ = scene_.render.height;
  filename_= scene_.render.filename;
  std::vector<Color> buffer(width_*height_, Color(0.0, 0.0, 0.0));
  colorbuffer_=buffer;
  PpmWriter ppm(width_, height_);
  ppm_ = ppm;

  // generate rays for the image
  std::vector<Ray> rays;
  scene_.cam.generate_rays(width_, height_, rays);

  // generate pixels for the rays
  std::vector<Pixel> pixel;
  for (unsigned i = 0; i < height_; ++i)
  {
    for (unsigned j = 0; j < width_; ++j)
    {
      Pixel p_temp(j,i);
      pixel.push_back(p_temp);
    }
  }


  std::vector<Pixel>::iterator j = pixel.begin();
  //raytrace color for each Pixel
  for (std::vector<Ray>::iterator i = rays.begin(); i < rays.end(); ++i)
  {
    Color temp = raytrace(*i,1);
    (*j).color = temp;
    write(*j);
    ++j;
  }
  //Save file
  ppm_.save(filename_);
}
