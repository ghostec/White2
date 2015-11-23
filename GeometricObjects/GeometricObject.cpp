#include "Utilities/Constants.h"
#include "GeometricObject.h"

GeometricObject::GeometricObject(void)
	: color(black)
{}

GeometricObject::GeometricObject (const GeometricObject& object)
	: color(object.color)
{}

GeometricObject&
GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	color = rhs.color;

	return (*this);
}

GeometricObject::~GeometricObject (void) {}

void
GeometricObject::add_object(GeometricObject* object_ptr) {}

Normal
GeometricObject::get_normal(void) const{
	return (Normal());
}

Normal
GeometricObject::get_normal(const Point3D& p) {
	return (Normal());
}

Point3D
GeometricObject::sample(void) {
	return (Point3D(0.0));
}

float
GeometricObject::pdf(ShadeRec& sr) {
	return (0.0);
}
