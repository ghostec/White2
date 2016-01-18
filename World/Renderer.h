#ifndef __RENDERER__
#define __RENDERER__

#include "World.h"
#include "Settings.h"

class Renderer {
public:
  Renderer();
  void render(int by, int ey);
  World world;
  Settings settings;
};

#endif
