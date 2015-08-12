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

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
 // , scene_()
{}

Renderer::Renderer()
  : width_(0)
  , height_(0)
  , colorbuffer_(0, Color(0.0, 0.0, 0.0))
  , filename_("")
  , ppm_(width_, height_)
 // , scene_()
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


Optional_hit Renderer::intersect(Ray const& ray /*,shapes*/) const{
  Optional_hit o;
  std::vector<float> dis;
  float distance;
  
  /*
  for (std::vector<std::shared_ptr <Shape>>::iterator it = scene_->shapes.begin(); it != scene_->shapes.end(); ++it)
  {
    Shape s = **it;
    s.intersect(ray, distance);
    dis.push_back(distance);
  }

  //suche geringste distance und passendes Shape dazu
  int min_pos = distance(dis.begin(), min_element(dis.begin(), dis.end()));
  o.shape = shapes[min_pos];
  */
  return o;
}

Color Renderer::raytrace(Ray const& ray, unsigned depth, Color const& ambient){
  Color c(0,0,0);
  if(depth == 0){
    //c
    return c;
  }
  else{
    Optional_hit o = intersect(ray);

    if(o.hit) {
      
      //woher kennt er alle Scene eigenschaften (ambient material..) 
      //--- evtl einen Scene* als Member?

      //render
      

      //temp
      return ambient;
      //return c;

      }
    else {
      return ambient;
      return c;
    }
  }
}


//ungefähres Prozedere? was ist mit den Methoden vom Bernstein?
void Renderer::render(std::string filename){

  Sdf_loader loader{filename};
  Scene scene = loader.load_scene(filename);

  width_ = scene.render.get_width();
  height_ = scene.render.get_height();
  filename_= scene.render.get_filename();

  
  std::vector<Ray> rays;
  scene.cam.generate_rays(width_, height_, rays);

  std::vector<Color> colors;
  unsigned depth = 1;
  
  for (std::vector<Ray>::iterator i = rays.begin(); i < rays.end(); ++i)
  {
    Color temp = raytrace(*i, depth, scene.ambient);
    colors.push_back(temp); 
  }
}