#ifndef __Point2D__
#define __Point2D__

#include "Vector3D.h"

class Point2D {
	public:

		double x, y, z;

		Point2D();
		Point2D(const double a);
		Point2D(const double a, const double b);
		Point2D(const Point2D& p);
		~Point2D();

    Point2D& operator= (const Point2D& p);
    Point2D operator- (void) const;
    Point2D operator* (const double a) const;
    double d_squared(const Point2D& p) const;
    double distance(const Point2D& p) const;
};

inline Point2D Point2D::operator- (void) const {
	return (Point2D(-x, -y));
}

inline Point2D
Point2D::operator* (const double a) const {
	return (Point2D(x * a, y * a));
}

inline double Point2D::d_squared(const Point2D& p) const {
	return ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

Point2D operator* (double a, const Point2D& p);

inline Point2D operator* (double a, const Point2D& p) {
	return (Point2D(a * p.x, a * p.y));
}

#endif
