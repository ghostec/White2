#ifndef __GEOMETRIC_OBJECTS_PRIMITIVES_PLANE__
#define __GEOMETRIC_OBJECTS_PRIMITIVES_PLANE__

#include "GeometricObjects/GeometricObject.h"
#include "Utilities/Point3D.h"
#include "Utilities/Normal.h"

class Plane : public GeometricObject {
private:
  Point3D point;
  Normal normal;
  static const double kEpsilon;
public:
	Plane(void);
	Plane(const Point3D _point, const Normal _normal);
	Plane(const Plane& p);

	virtual Plane* clone(void) const;
	virtual ~Plane(void);
	Plane& operator= (const Plane& Plane);
	void setPoint(const Point3D& _point);
	void setNormal(const Normal& _normal);
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
  virtual bool shadowHit(const Ray& ray, double& tmin) const;
};

inline void Plane::setPoint(const Point3D& _point) {
	point = _point;
}

inline void Plane::setNormal(const Normal& _normal) {
  normal = _normal;
}

#endif
