#include <iostream>
#include "World/World.h"
#include "Cameras/Pinhole.h"

int main() {
  World w;
  w.build();
  //w.render_perspective();
  Pinhole p;
  p.set_eye(Point3D(0, 50, 60));
  p.set_lookat(Point3D(0, 0, 0));
  p.set_up(Vector3D(0, 1, 0));
  p.d = 200;
  p.compute_uvw();
  p.render_scene(w);
  return 0;
}
