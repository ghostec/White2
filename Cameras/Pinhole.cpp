#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include "Camera.h"
#include "Pinhole.h"

Pinhole::Pinhole() {}

Pinhole::Pinhole(const Pinhole& _p) : CameraWorker(_p), d(_p.d), zoom(_p.zoom) {}

CameraWorker* Pinhole::clone() const
{
  return new Pinhole(*this);
}

void Pinhole::render(World& w, int o_y, int e_y)
{
  RGBColor pixel_color;
  Ray ray;
  Point2D sp;
  Point2D pp;

  auto& canvas = w.vp.canvas;
  int hres = w.vp.hres;

  ray.o = eye;
  for(int r = o_y; r < e_y; r++) {
    for(int c = 0; c < hres; c++) {
      pixel_color = black;
      for(int j = 0; j < w.vp.num_samples; j++) {
        sp = w.vp.sampler_ptr->sample_unit_square();
        pp.x = w.vp.s * (c - 0.5 * w.vp.hres + sp.x);
        pp.y = w.vp.s * (r - 0.5 * w.vp.vres + sp.y);
        ray.d = rayDirection(pp);
        pixel_color += w.tracer_ptr->trace_ray(ray, 0);
      }
      pixel_color /= w.vp.num_samples;
      canvas[hres*r + c] = pixel_color;
    }
  }
  // Check states: terminate...
}

Vector3D Pinhole::rayDirection(const Point2D & p)
{
  Vector3D dir = p.x * u + p.y * v - d * w;
  dir.normalize();
  return dir;
}
