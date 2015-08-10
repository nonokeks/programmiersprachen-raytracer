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

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

Renderer::Renderer()
  : width_(0)
  , height_(0)
  , colorbuffer_(0, Color(0.0, 0.0, 0.0))
  , filename_("")
  , ppm_(width_, height_)
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


Optional_hit Renderer::intersect(Ray const& ray) const{
  Optional_hit o;
  return o;
}

Color Renderer::raytrace(Ray const& ray, unsigned depth, Color const& ambient){
  if(depth == 0){
    Color c(0,0,0);
    return c;
  }
  else{
    Optional_hit o = intersect(ray);

    if(o.hit) {
      
      //bei mehreren Hits -> welches Shape am vordersten?
      //woher kennt er alle Scene eigenschaften (ambient material..) 
      //--- evtl einen Scene* als Member?

      //render
      

      //temp
      return ambient;

      }
    else return ambient;
  }
}