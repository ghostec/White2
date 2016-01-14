#include "Cameras/Pinhole.h"
#include "Renderer.h"

Renderer::Renderer() : world(), camera() {
  settings.setNWorkers(8);

  world.build(settings);

  Pinhole* p = new Pinhole();
  p->setEye(Point3D(25, 20, 45));
  p->setLookat(Point3D(0, 1, 0));
  p->setUp(Vector3D(0, 1, 0));
  p->d = 5000;
  p->computeUvw();

  camera.setCameraWorker(p);
}

void Renderer::render(int by, int ey) {
  camera.render(settings, world, by, ey);
}