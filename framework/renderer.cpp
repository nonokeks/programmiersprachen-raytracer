// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "optional_hit.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "sdf_loader.hpp"
#include "color.hpp"
#include "shape.hpp"
#include <algorithm> // min_element


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



void Renderer::render()
{
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

void Renderer::write(Pixel const& p)
{
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
  std::vector<float> dis;
  float distance;
  
  
  for (std::vector<std::shared_ptr <Shape>>::const_iterator it = scene_.shapes.begin(); it != scene_.shapes.end(); ++it)
  {
    std::shared_ptr <Shape> s_ptr = *it;
    //Shape s = *s_ptr;
    o.hit = s_ptr->intersect_optional(ray, distance, o.intersection, o.normal);
    dis.push_back(distance);
  }

  //suche geringste distance und passendes Shape dazu
  int min_pos = std::distance(dis.begin(), std::min_element(dis.begin(), dis.end()));
  o.shape = &*scene_.shapes[min_pos];
  o.distance = *std::min_element(dis.begin(), dis.end());
	
  //normal, ... berechnen
  
  return o;
}

Color Renderer::raytrace(Ray const& ray){
  Optional_hit o = intersect(ray);
  if(o.distance == 0){ //ehemalige depth
    return scene_.ambient;
  }

  if(o.hit) {
    //Light_source l{"licht", {0,0,0}, {1.0,1.0,1.0}, {0.4,0.4,0.4}}; 
    //Schleife für alle lights?
    Light_source l = scene_.lights[0];
    float tmp = glm::dot(glm::normalize(ray.direction), glm::normalize(l.get_position() - o.intersection)); //intersection ausrechnen lassen bei intersect!
    Material temp_mat = scene_.material[(*o.shape).get_material()];
    float red = temp_mat.get_kd().r * l.get_diffuse().r * tmp;
    float green = temp_mat.get_kd().g * l.get_diffuse().g * tmp;
    float blue = temp_mat.get_kd().b * l.get_diffuse().b * tmp;
    std::cout << tmp << std::endl;
    return Color(red, green, blue);

     
  } 
  else {
    return scene_.ambient;
  }
  
}


//ungefähres Prozedere? was ist mit den Methoden vom Bernstein?
void Renderer::render_scene(std::string filename){

  //Scene wird geladen
  Sdf_loader loader{filename};
  scene_ = loader.load_scene(filename);

  //Daten aus Transferobejkt in den Renderer schreiben
  width_ = scene_.render.width;
  height_ = scene_.render.height;
  filename_= scene_.render.filename;
  std::vector<Color> buffer(width_*height_, Color(0.0, 0.0, 0.0));
  colorbuffer_=buffer;
  PpmWriter ppm(width_, height_);
  ppm_ = ppm;


  //Rays für das Bild gernerieren
  std::vector<Ray> rays;
  scene_.cam.generate_rays(width_, height_, rays);
  std::cout << rays.size() << std::endl;
  
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
  //Farbe für jeden Pixel berechnen
  for (std::vector<Ray>::iterator i = rays.begin(); i < rays.end(); ++i)
  {
    Color temp = raytrace(*i);
    (*j).color = temp;
    ++j;
    write(*j);
  }
  ppm_.save(filename_);
}
