#include "Plane.h"
#include "math.h"

const double Plane::kEpsilon = 0.001;

Plane::Plane(void) : GeometricObject(), point(0.0), normal(0.0, 1.0, 0.0) {}

Plane::Plane(const Point3D _point, const Normal _normal) : GeometricObject(), point(_point), normal(_normal) {}

Plane* Plane::clone(void) const {
	return (new Plane(*this));
}

Plane::Plane(const Plane& p) : GeometricObject(p), point(p.point), normal(p.normal) {}

Plane& Plane::operator= (const Plane& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	point 	= rhs.point;
	normal	= rhs.normal;

	return (*this);
}

Plane::~Plane(void) {}

bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double t = (normal * (point - ray.o)) / (normal * ray.d);

  if(t > kEpsilon) {
    tmin = t;
    sr.normal = normal;
    sr.local_hit_point = ray.o + t * ray.d;
    return true;
  }

	return false;
}

bool Plane::shadowHit(const Ray& ray, double& tmin) const
{
  double t = (normal * (point - ray.o)) / (normal * ray.d);

  if(t > kEpsilon) {
    tmin = t;
    return true;
  }

  return false;
}
