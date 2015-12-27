#include "Camera.h"
#include "Pinhole.h"
#include <iostream>

void Pinhole::render_scene(World& w)
{
  RGBColor pixel_color;
  Ray ray;
  Point2D sp;
  Point2D pp;

  ray.o = eye;

  for(int r = 0; r < w.vp.vres; r++) {
    for(int c = 0; c < w.vp.hres; c++) {
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
      mq.push({ MessagePixel_e::Pixel, c, r, pixel_color });
    }
  }
  mq.push({ MessagePixel_e::Done, 0, 0, black });
  //w.vp.save_image();
}

Pinhole::Pinhole(MessageQueue<MessagePixel>& _mq) : Camera(_mq) {}

Vector3D Pinhole::ray_direction(const Point2D & p)
{
  Vector3D dir = p.x * u + p.y * v - d * w;
  dir.normalize();
  return dir;
}
