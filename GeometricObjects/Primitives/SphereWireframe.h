#ifndef __GEOMETRI_COBJECTS_PRIMITIVES_SPHERE_WIREFRAME__
#define __GEOMETRI_COBJECTS_PRIMITIVES_SPHERE_WIREFRAME__

#include "GeometricObjects/GeometricObject.h"

class SphereWireframe: public GeometricObject {
private:
  Point3D center;
  double radius;
  static const double kEpsilon;
public:
	SphereWireframe(void);
	SphereWireframe(Point3D center, double r);
	SphereWireframe(const SphereWireframe& SphereWireframe);

	virtual SphereWireframe* clone(void) const;
	virtual ~SphereWireframe(void);
	SphereWireframe& operator= (const SphereWireframe& SphereWireframe);
	void set_center(const Point3D& c);
	void set_center(const double x, const double y, const double z);
	void set_radius(const double r);
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
  virtual bool shadowHit(const Ray& ray, double& tmin) const;
};

inline void SphereWireframe::set_center(const Point3D& c) {
	center = c;
}

inline void SphereWireframe::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}

inline void SphereWireframe::set_radius(const double r) {
	radius = r;
}

#endif
