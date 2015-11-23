#include <math.h>
#include "Point3D.h"

Point3D::Point3D()
	:x(0), y(0), z(0)
{}

Point3D::Point3D(const double a)
	:x(a), y(a), z(a)
{}

Point3D::Point3D(const double a, const double b, const double c)
	:x(a), y(b), z(c)
{}

Point3D::Point3D(const Point3D& p)
	:x(p.x), y(p.y), z(p.z)
{}

Point3D::~Point3D()
{}

Point3D&
Point3D::operator= (const Point3D& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}

double
Point3D::distance(const Point3D& p) const {
	return (sqrt(		(x - p.x) * (x - p.x)
					+ 	(y - p.y) * (y - p.y)
					+	(z - p.z) * (z - p.z) ));
}
