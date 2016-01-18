#include <iostream>
#include "Utilities/Vector3D.h"
#include "SphereWireframe.h"
#include "World/World.h"
#include "math.h"

const double SphereWireframe::kEpsilon = 0.001;

SphereWireframe::SphereWireframe(void) : GeometricObject(), center(0.0), radius(1.0) {}

SphereWireframe::SphereWireframe(Point3D c, double r) : GeometricObject(), center(c), radius(r) {}

SphereWireframe* SphereWireframe::clone(void) const {
	return new SphereWireframe(*this);
}

SphereWireframe::SphereWireframe(const SphereWireframe& SphereWireframe) :
  GeometricObject(SphereWireframe), center(SphereWireframe.center), radius(SphereWireframe.radius) {}

SphereWireframe& SphereWireframe::operator= (const SphereWireframe& rhs)
{
	if(this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;

	return (*this);
}

SphereWireframe::~SphereWireframe(void) {}

bool SphereWireframe::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  Vector3D normal = center - sr.w.camera->getCameraWorker()->getEye();
  double t = (normal * (center - ray.o)) / (normal * ray.d);
  double threshold = 0.03;
  Point3D point = ray.o + t * ray.d;
  double dist = (point - center).length();

  if(t > kEpsilon && dist <= radius && (radius - dist) <= threshold) {
    tmin = 0.0;
    sr.normal = normal;
    sr.local_hit_point = point;
    return true;
  }

	return false;
}

bool SphereWireframe::shadowHit(const Ray& ray, double& tmin) const
{
  return false;
}
