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

#include <algorithm> // min_element
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>

#include "camera.hpp"
#include "color.hpp"
#include "composite.hpp"
#include "optional_hit.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "sdf_loader.hpp"
#include "shape.hpp"

class Renderer {
	public:
	  Renderer(unsigned w, unsigned h, std::string const& file);
	  Renderer();

	  void render();
	  void write(Pixel const& p);

	  inline std::vector<Color> const& colorbuffer() const{
		return colorbuffer_;
	  }

	  unsigned get_width() const;
	  unsigned get_height() const;
	  std::string get_filename() const;
	  Scene get_scene() const;

	  Renderer& operator= (Renderer const& rhs);

	  Optional_hit intersect(Ray const& ray) const;

	  Color raytrace(Ray const& ray, int depth);
	  void render_scene(std::string filename); 
	  Ray reflect_ray(glm::vec3 const& intersection, glm::vec3 const& normale, glm::vec3 const& rayDirection) const;
	  //Color shade(Ray const& ray, Optional_hit const& o); //weg?
	  Color shade(Ray const& ray, Optional_hit const& o, int depth);

	private:
	  unsigned width_;
	  unsigned height_;
	  std::vector<Color> colorbuffer_;
	  std::string filename_;
	  PpmWriter ppm_;
	  Scene scene_;
};

#endif // #ifndef BUW_RENDERER_HPP
