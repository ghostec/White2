#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "World/World.h"
#include "Cameras/Camera.h"
#include "Cameras/Pinhole.h"

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

int main(int argc, char *argv[]) {
  World w;
  w.build();

  Pinhole p;
  p.setEye(Point3D(0, 25, 50));
  p.setLookat(Point3D(0, 0, 0));
  p.setUp(Vector3D(0, 1, 0));
  p.d = 200;
  p.computeUvw();

  Camera cam;
  cam.setCameraWorker(p);

  cam.render(w);

  return 0;
}
