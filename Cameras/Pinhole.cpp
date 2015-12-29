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

void Pinhole::render_scene(int tid, World& w, int o_x, int o_y, int e_x, int e_y)
{
  RGBColor pixel_color;
  Ray ray;
  Point2D sp;
  Point2D pp;

  ray.o = eye;

  canvas.setSize(e_x - o_x, e_y - o_y);

  for(int r = o_y; r < e_y; r++) {
    for(int c = o_x; c < e_x; c++) {
      pixel_color = black;
      for(int j = 0; j < w.vp.num_samples; j++) {
        sp = w.vp.sampler_ptr->sample_unit_square();
        pp.x = w.vp.s * (c - 0.5 * w.vp.hres + sp.x);
        pp.y = w.vp.s * (r - 0.5 * w.vp.vres + sp.y);
        ray.d = ray_direction(pp);
        pixel_color += w.tracer_ptr->trace_ray(ray);
      }
      pixel_color /= w.vp.num_samples;
      //w.vp.canvas[r*w.vp.vres + c] = pixel_color;
      canvas.setPixel(c - o_x, r - o_y, pixel_color);
    }
  }
  //w.vp.save_image();
}

Vector3D Pinhole::ray_direction(const Point2D & p)
{
  Vector3D dir = p.x * u + p.y * v - d * w;
  dir.normalize();
  return dir;
}
