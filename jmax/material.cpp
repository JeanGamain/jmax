#include "material.hpp"
#include "engine.hpp"

#include <iostream>

namespace jmax
{
  material::material()
    : transparency(0), reflexion(0),
      map_Ka(0), map_Kd(0), map_Ks(0), map_bump(0)
  {
    ambient.integer = 255;
    diffuse.integer = 255;
    specular.integer = 255;
  }
  
  material::~material()
  {
  }
  
  void	material::setup() const
  {
    
    if (map_Kd != 0) {
      std::cout << "map_Kd_id" << map_Kd << std::endl;
      glBindTexture(GL_TEXTURE_2D, map_Kd);
      glPopAttrib();
    } else {
      glColor4ubv(reinterpret_cast<const GLubyte*>(&diffuse));
    }
  }
}
