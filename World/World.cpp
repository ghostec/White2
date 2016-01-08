#include <algorithm>
#include <cstdio>
#include <iostream>
#include "Utilities/Vector3D.h"
#include "Utilities/Point3D.h"
#include "Utilities/Point2D.h"
#include "Utilities/Normal.h"
#include "Utilities/Ray.h"
#include "Tracers/RayCast.h"
#include "Tracers/MultipleObjects.h"
#include "Samplers/Jittered.h"
#include "Lights/Ambient.h"
#include "Lights/PointLight.h"
#include "Materials/Matte.h"
#include "Materials/Phong.h"
#include "GeometricObjects/Primitives/Sphere.h"
#include "GeometricObjects/Primitives/Plane.h"
#include "World.h"

World::World(void) : background_color(black), tracer_ptr(nullptr), ambient_light(new Ambient) {}

void World::build(void) {
  int num_samples = 4;
  vp.setSize(600, 600);
  vp.setPixelSize(1);
  vp.setGamma(1.0);
  vp.setSampler(std::unique_ptr<Jittered>(new Jittered(num_samples)));

  background_color = black;
  tracer_ptr = std::unique_ptr<Tracer>(new RayCast(this));

  Ambient* ambient_ptr = new Ambient;
  ambient_ptr->scaleRadiance(0.25);
  ambient_light = ambient_ptr;

  PointLight* light_ptr2 = new PointLight;
  light_ptr2->setLocation(Point3D(40, 60, 30));
  light_ptr2->scaleRadiance(5.0);
  lights.push_back(light_ptr2);

  Matte* matte_ptr1 = new Matte;
  matte_ptr1->setKa(0.25);
  matte_ptr1->setKd(0.65);
  matte_ptr1->setCd(1, 1, 0);

	Sphere* sphere_ptr = new Sphere;
  sphere_ptr->set_center(0, 15, -30);
  sphere_ptr->set_radius(15.0);
  sphere_ptr->set_color(1, 0, 0);
  sphere_ptr->setMaterial(matte_ptr1);
	add_object(sphere_ptr);

  Phong* phong_ptr1 = new Phong;
  phong_ptr1->setKa(0.15);
  phong_ptr1->setKd(0.70);
  phong_ptr1->setCd(1, 0, 0);
  phong_ptr1->setKs(0.15);
  phong_ptr1->setCs(1, 1, 1);
  phong_ptr1->setExp(10.0);

	sphere_ptr = new Sphere(Point3D(0, 15, 30), 15);
	sphere_ptr->set_color(0, 0, 1);
  sphere_ptr->setMaterial(phong_ptr1);
	add_object(sphere_ptr);

  Matte* matte_ptr3 = new Matte;
  matte_ptr3->setKa(0.25);
  matte_ptr3->setKd(0.65);
  matte_ptr3->setCd(0, 0, 1);

  sphere_ptr = new Sphere(Point3D(-30, 5, 35), 10);
  sphere_ptr->set_color(1, 1, 0);
  sphere_ptr->setMaterial(matte_ptr3);
  add_object(sphere_ptr);

  Plane* plane_ptr = new Plane;
  Matte* matte_ptr4 = new Matte;
  matte_ptr4->setKa(0.25);
  matte_ptr4->setKd(0.65);
  matte_ptr4->setCd(0.6, 0.6, 0.6);
  plane_ptr->setMaterial(matte_ptr4);
  add_object(plane_ptr);
}

inline void World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

void World::addLight(Light * light_ptr)
{
  lights.push_back(light_ptr);
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

ShadeRec World::hit_objects(const Ray& ray)
{
  ShadeRec sr(*this);
  double t;
  Normal normal;
  Point3D local_hit_point;
  double tmin = kMAX_DOUBLE;
  int n_objects = objects.size();

  for(int i = 0; i < n_objects; i++) {
    if(objects[i]->hit(ray, t, sr) && (t < tmin)) {
      sr.hit_an_object = true;
      tmin = t;
      sr.material_ptr = objects[i]->getMaterial();
      sr.hit_point = ray.o + t * ray.d;
      normal = sr.normal;
      local_hit_point = sr.local_hit_point;
    }
  }

  if(sr.hit_an_object) {
    sr.t = tmin;
    sr.normal = normal;
    sr.local_hit_point = local_hit_point;
  }

  return sr;
}
