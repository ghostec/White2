#include <algorithm>
#include <cstdio>
#include "Utilities/Vector3D.h"
#include "Utilities/Point3D.h"
#include "Utilities/Normal.h"
#include "Utilities/Ray.h"
#include "Tracers/MultipleObjects.h"
#include "World.h"

World::World(void)
	: background_color(black), tracer_ptr(nullptr)
{}

void
World::build(void) {
  vp.set_hres(200);
  vp.set_vres(200);
  vp.set_pixel_size(1);
  vp.set_gamma(1.0);

  canvas.resize(200*200);

  background_color = black;
  tracer_ptr = std::unique_ptr<Tracer>(new MultipleObjects(this));

	Sphere* sphere_ptr = new Sphere;
  sphere_ptr->set_center(0, -25, 0);
  sphere_ptr->set_radius(80.0);
  sphere_ptr->set_color(1, 0, 0);
	add_object(sphere_ptr);

	sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
	sphere_ptr->set_color(1, 1, 0);
	add_object(sphere_ptr);
}

void
World::render_scene(void) {
  RGBColor pixel_color;
  Ray ray;
  double zw = 100.0;
  double x, y;

  ray.d = Vector3D(0, 0, -1);

  for(int r = 0; r < vp.vres; r++) {
    for(int c = 0; c < vp.hres; c++) {
      x = vp.s * (c - 0.5 * (vp.hres - 1.0));
      y = vp.s * (r - 0.5 * (vp.vres - 1.0));
      ray.o = Point3D(x, y, zw);
      pixel_color = tracer_ptr->trace_ray(ray);
      canvas[r*vp.vres + c] = pixel_color;
    }
  }
  save_image();
}

inline double clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }

void
World::save_image() {
  FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", vp.hres, vp.vres, 255);
  for(int i = vp.vres * vp.vres - 1; i >= 0; i--)
  fprintf(f,"%d %d %d ", toInt(canvas[i].r), toInt(canvas[i].g), toInt(canvas[i].b));
}

inline void
World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

ShadeRec
World::hit_bare_bones_objects(const Ray& ray) {
	ShadeRec sr(*this);
	double t, tmin = kMAX_DOUBLE;
	int num_objects = objects.size();
	for(int i = 0; i < num_objects; i++) {
		if(objects[i]->hit(ray, t, sr) && t < tmin) {
			sr.hit_an_object = true;
			sr.color = objects[i]->get_color();
			tmin = t;
		}
	}
	return sr;
}
