#ifndef __RENDERER__
#define __RENDERER__

#include "Cameras/Camera.h"
#include "World.h"

class Renderer {
public:
  Renderer();
  void render(int by, int ey);
  World world;
  Camera camera;
  // ViewPlane
};

#endif
