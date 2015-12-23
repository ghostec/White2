#include <algorithm>
#include <cstdio>
#include <iostream>
#include "Utilities/Vector3D.h"
#include "Utilities/Point3D.h"
#include "Utilities/Point2D.h"
#include "Utilities/Normal.h"
#include "Utilities/Ray.h"
#include "Tracers/MultipleObjects.h"
#include "Samplers/Jittered.h"
#include "World.h"

World::World(void) : background_color(black), tracer_ptr(nullptr) {}

void World::build(void) {
  int num_samples = 1;
  vp.set_hres(600);
  vp.set_vres(600);
  vp.set_pixel_size(1);
  vp.set_gamma(1.0);
  vp.set_sampler(std::unique_ptr<Jittered>(new Jittered(num_samples)));

  vp.canvas.resize(600*600);

  background_color = black;
  tracer_ptr = std::unique_ptr<Tracer>(new MultipleObjects(this));

	Sphere* sphere_ptr = new Sphere;
  sphere_ptr->set_center(0, 0, -30);
  sphere_ptr->set_radius(15.0);
  sphere_ptr->set_color(1, 0, 0);
	add_object(sphere_ptr);

	sphere_ptr = new Sphere(Point3D(0, 0, 30), 15);
	sphere_ptr->set_color(0, 0, 1);
	add_object(sphere_ptr);
}

inline void World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

ShadeRec World::hit_bare_bones_objects(const Ray& ray) {
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
