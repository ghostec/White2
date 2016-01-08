#include "Cameras/Pinhole.h"
#include "Renderer.h"

Renderer::Renderer() : world(), camera() {
  world.build();

  Pinhole* p = new Pinhole();
  p->setEye(Point3D(0, 40, 50));
  p->setLookat(Point3D(0, 0, 0));
  p->setUp(Vector3D(0, 1, 0));
  p->d = 200;
  p->computeUvw();

  camera.setCameraWorker(p);
}

void Renderer::render(int by, int ey) {
  camera.render(world, by, ey);
}