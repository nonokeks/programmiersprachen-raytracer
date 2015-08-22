#include <thread>
#include "renderer.hpp"
#include <fensterchen.hpp>

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;

  //std::string const filename = "./checkerboard.ppm";
  //Renderer app(width, height, filename);

  Renderer r;

  r.render_scene("./test.txt"); 



  //std::thread thr([&r]() { r.render(); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

   // glDrawPixels( width, height, GL_RGB, GL_FLOAT
  //             , r.colorbuffer().data());
    std::vector<Color> color = r.colorbuffer();
    int c = 0;
    for (int y = -(height/2); y < height/2; ++y)
    {
      for (int x = -(width/2); x < width/2; ++x)
      {
        glDrawPixels(x, y, GL_RGB, GL_FLOAT, color.data());
        ++c;
      }
    }
    


    win.update();
  }

  //thr.join();

  return 0;
}
