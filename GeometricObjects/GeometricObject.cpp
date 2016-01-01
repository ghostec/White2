#include <iostream>
#include "Utilities/Constants.h"
#include "GeometricObject.h"

GeometricObject::GeometricObject(void) : color(black), material_ptr(nullptr) {}

GeometricObject::GeometricObject (const GeometricObject& object)
	: color(object.color), material_ptr(object.material_ptr)
{}

GeometricObject&
GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	color = rhs.color;
  material_ptr = rhs.material_ptr;

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

void GeometricObject::setMaterial(Material* _material_ptr)
{
  material_ptr = _material_ptr;
}

Material* GeometricObject::getMaterial(void) const
{
  return material_ptr;
}

Point3D
GeometricObject::sample(void) {
	return (Point3D(0.0));
}

float
GeometricObject::pdf(ShadeRec& sr) {
	return (0.0);
}
