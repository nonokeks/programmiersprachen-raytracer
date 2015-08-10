// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "ray.hpp"
#include "optional_hit.hpp"

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer();

  void render();
  void write(Pixel const& p);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }


  //------- new

  //getter
  unsigned get_width() const;
  unsigned get_height() const;
  std::string get_filename() const;

  Renderer& operator= (Renderer const& rhs);

  Optional_hit intersect(Ray const& ray) const;

  Color raytrace(Ray const& ray, unsigned depth, Color const& ambient);


private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
