#include "Cameras/Pinhole.h"
#include "Renderer.h"

Renderer::Renderer() : world() {
  settings.setNWorkers(8);
  settings.setNSamples(49);
  settings.vres = settings.hres = 600;

  world.build(settings);

  Pinhole* p = new Pinhole();
  p->setEye(Point3D(1, 1, 45));
  p->setLookat(Point3D(0, 1, 0));
  p->setUp(Vector3D(0, 1, 0));
  p->d = 5000;
  p->computeUvw();

  Camera* c = new Camera();
  world.camera = c;
  world.camera->setCameraWorker(p);
}

void Renderer::render(int by, int ey) {
  world.camera->render(settings, world, by, ey);
}
