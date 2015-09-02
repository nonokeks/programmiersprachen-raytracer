#include <thread>
#include "renderer.hpp"
#include <fensterchen.hpp>
#include <iostream> 
#include <string> 
#include <sstream>
#include <vector>

#include <fstream> 
#include <cstdio>
#include <cstdlib>

//Convert number to string
template<typename T> 
std::string toString(T x) 
{ 
    std::ostringstream result; 
    result << x; 
    return result.str(); 
} 

int main(int argc, char* argv[])
{

  //file path
  std::string save = "~\\Dokumente\\PLSE\\programmiersprachen-raytracer\\";
  save += "build\\build\\Release\\picture";
  std::string txt = ".txt";
  std::string ppm = ".ppm";
  std::string nullnull = "00";
  std::string null = "0";
  std::vector<std::string> dateien;

  //Content of Scene
  std::string geometry = "define shape sphere sphere1 20 20 -100 10 red\n";
  geometry += "define shape box rbottom 0.2 0.7 -5 1.6 1.2 -8 green\n"; 
  geometry += "define shape triangle triangle1 -20 20 -100 20 20 -100 -10 -10";
  geometry += " -100 blue\n";
  geometry += "define shape sphere sphere3 -2 -2 -15 2 yellow\n";
  std::string materials = "define material green 0 1 0 0 1 0 0 1 0 0 0 0\n";
  materials += "define material red 1 0 0 1 0 0 1 0 0 0 0 0\n";
  materials += "define material blue 0 0 1 0 0 1 0 0 1 0 0 0\n";
  materials += "define material yellow 1 1 0 1 1 0 1 1 0 0 0 0\n";
  std::string lights = "define light sun 1000 700 0 0.2 0.2 0.2 0.8 0.8 0.8\n";
  lights += "define light lamp 50 50 10 0.3 0.3 0.3 0.3 0.3 0.3\n";
  std::string composite = "define shape composite sphere1 rbottom triangle1";
  composite += " sphere3\n";
  
  std::string name = "";
  std::string bild = "picture";
  std::string renderer= "render cam ";
  std::string masse = " 600 600\n";
  std::string camera = "camera cam 45 ";

  Renderer r;

  for (int i = 1; i < 181; ++i)
  {
    
    name = "";
    bild = "picture";
    camera = "camera cam 45 ";
    renderer= "render cam ";
    masse = " 600 600\n";

    if (i < 10)
    {
      name = save + nullnull + toString(i) + txt;
      bild += nullnull + toString(i) + ppm;
    }
    else if (i < 100)
    {
      name = save + null + toString(i) + txt;
      bild += null + toString(i) + ppm;
    }
    else
    {
      name = save + toString(i) + txt;
      bild += toString(i) + ppm;
    }
    dateien.push_back(name);

    renderer += bild + masse;

    //Position
    camera += toString(10) + " " + toString(0) + " " + toString(-10) + " ";
    //view
    camera += toString((float)-i/20) + " " + toString(0) + " " + toString(-1)
               + " ";
    //UPvector
    camera += toString(0) + " " + toString(1) + " " + toString(0) + "\n";

    
    std::ofstream data;
    data.open(name, std::ios::out);
   
    data << geometry << materials << lights << renderer << camera << composite;

    data.close();

    //render scene
    r.render_scene(name);

  }
  

  return 0;
}
