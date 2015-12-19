#include <math.h>
#include "Point2D.h"

Point2D::Point2D() :x(0), y(0), z(0) {}

Point2D::Point2D(const double a) :x(a), y(a), z(a) {}

Point2D::Point2D(const double a, const double b) :x(a), y(b) {}

Point2D::Point2D(const Point2D& p) : x(p.x), y(p.y) {}

Point2D::~Point2D() {}

Point2D& Point2D::operator= (const Point2D& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y;

	return (*this);
}

double Point2D::distance(const Point2D& p) const {
	return (sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)));
}
