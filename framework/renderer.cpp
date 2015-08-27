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
#include <glm/glm.hpp>


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
    o.hit = s_ptr->intersect(ray, distance, o.intersection, o.normal);
    dis.push_back(distance);
  }

  //suche geringste distance und passendes Shape dazu
  int min_pos = std::distance(dis.begin(), std::min_element(dis.begin(), dis.end()));
  o.shape = &*scene_.shapes[min_pos];
  o.distance = *std::min_element(dis.begin(), dis.end());
	
  
  
  return o;
}

Color Renderer::raytrace(Ray const& ray){
  Optional_hit o = intersect(ray);
  //reflect, wieder intersect, shade, usw hier rein?
  if(o.hit) return shade(ray, o);
  else return scene_.ambient;
}

Color Renderer::shade(Ray const& ray, Optional_hit const& o)const{ //braucht man noch color und recursion depth statt distance? wenn ja woher?
	
  //Light_source l{"licht", {0,0,0}, {1.0,1.0,1.0}, {0.4,0.4,0.4}}; 
  //Schleife für alle lights?
  Light_source light = scene_.lights[0];
  Material temp_mat = scene_.material[(*o.shape).get_material()];
  float r = 0, g = 0, b = 0;
  float red = 0, green = 0, blue = 0;

  for(std::vector<Light_source>::const_iterator l = scene_.lights.begin(); l != scene_.lights.end(); ++l)
  {

    //Ray von Schnittpunkt zu Lichtquelle
    Ray lightray(o.intersection, glm::normalize((*l).get_position()));

    //Lichtintensität (Skalarprodukt, wird dann mit Reflexionskoeffizient und Helligkeit der Lichtquelle multipliziert)
    //oder Winkel zwischen Normale und Lichtquelle 
    float tmp = glm::dot(o.normal, glm::normalize((*l).get_position()-o.intersection) );

    float temp_r = 0, temp_g = 0, temp_b = 0;

    Optional_hit shadow = intersect(lightray);
    if(!shadow.hit){

      //Winkel Kamera/Lichquelle
      float cam_light_angle = glm::dot(glm::normalize(o.intersection - scene_.cam.get_position()), glm::normalize((*l).get_position() - o.intersection));


      /* Reflection ??
      float reflection = cam_light_angle - (2* tmp);

      //Reflektionsvecktor ?
      glm::vec3 reflect_vec((2 * tmp * o.normal.x - (*l).get_position().x), (2 * tmp * o.normal.y - (*l).get_position().y), (2 * tmp * o.normal.z - (*l).get_position().z));

      Ray reflection_ray(o.intersection, reflect_vec);
      //oder Ray reflection_ray = reflect_ray(o.intersection, o.normale, l.get_position()); ?

      
      temp_r = temp_mat.get_ks().r; //* pow(reflection, ke);
      temp_g = temp_mat.get_ks().g; //* pow(reflection, ke);
      temp_b = temp_mat.get_ks().b; //* pow(reflection, ke);
      */

      r += (*l).get_diffuse().r * (tmp * temp_mat.get_kd().r + temp_mat.get_ks().r);
      g += (*l).get_diffuse().g * (tmp * temp_mat.get_kd().g + temp_mat.get_ks().g);
      b += (*l).get_diffuse().b * (tmp * temp_mat.get_kd().b + temp_mat.get_ks().b);

    }
    else{
      //Wenn im Schatten werden die Werde berechnet, sonst 0 ( Operator shadow.hit ? 1 : 0)
      r += temp_mat.get_kd().r * (*l).get_diffuse().r * tmp;
      g += temp_mat.get_kd().g * (*l).get_diffuse().g * tmp;
      b += temp_mat.get_kd().b * (*l).get_diffuse().b * tmp;
    }
  
  }
  //mit Ambiente
  red = temp_mat.get_ka().r * light.get_ambiente().r + r;
  green = temp_mat.get_ka().g * light.get_ambiente().g + g;
  blue = temp_mat.get_ka().b * light.get_ambiente().b + b;


  return Color(red, green, blue);

}


//ungefähres Prozedere? was ist mit den Methoden vom Bernstein?
void Renderer::render_scene(std::string filename){

  //Scene wird geladen
  Sdf_loader loader{filename};
  scene_ = loader.load_scene(filename);

  //Daten aus Transferobjekt in den Renderer schreiben
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
  //std::cout << rays.size() << std::endl;
  
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
    write(*j);
    ++j;
  }
  ppm_.save(filename_);
  
  
}

//warum haben wir render und render_scene?


Ray Renderer::reflect_ray(glm::vec3 const& intersection, glm::vec3 const& normale, glm::vec3 const& rayDirection) const{
	//float normaleLength = sqrt(normale.x*normale.x + normale.y*normale.y + normale.z*normale.z); //Länge eines Vektors
	//glm::vec3 n{(normale.x/normaleLength), (normale.y/normaleLength), (normale.z/normaleLength)}; //normale normiert
  //normale ist normiert
	glm::vec3 spiegel{0.0f, 0.0f, 0.0f}; //neuer Ray direction kommt hier rein, origin ist intersection
	spiegel.x = (2*normale.x*normale.x*rayDirection.x + 2*normale.x*normale.y*rayDirection.y + 2*normale.x*normale.z*rayDirection.z - rayDirection.x);
	spiegel.y = (2*normale.x*normale.y*rayDirection.x + 2*normale.x*normale.y*rayDirection.y + 2*normale.y*normale.z*rayDirection.z - rayDirection.y);
	spiegel.z = (2*normale.y*normale.z*rayDirection.x + 2*normale.y*normale.z*rayDirection.y + 2*normale.z*normale.z*rayDirection.z - rayDirection.z);
	Ray newRay{intersection, spiegel}; //spiegel muss vielleicht *-1 genommen werden, bin mir nicht sicher ob der in die richtige Richtung zeigt
	return newRay;

}
