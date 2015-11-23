#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include <math.h>

#include "Utilities/Constants.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "Utilities/Normal.h"
#include "Utilities/Ray.h"
#include "Utilities/ShadeRec.h"

class GeometricObject {
	public:
		GeometricObject(void);
		GeometricObject(const GeometricObject& object);

		virtual GeometricObject*
		clone(void) const = 0;

		virtual
		~GeometricObject(void);

		virtual bool
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

		void
		set_color(const RGBColor& c);

		void
		set_color(const float r, const float g, const float b);

		RGBColor
		get_color(void);

		virtual void
		add_object(GeometricObject* object_ptr);

		// The following two functions are only required for objects that are light sources, eg disks, rectangles, and spheres

		virtual Point3D
		sample(void);

		virtual float
		pdf(ShadeRec& sr);

		// The following two functions allow us to simplify the code for smooth shaded triangle meshes

		virtual Normal
		get_normal(void) const;

		virtual Normal
		get_normal(const Point3D& p);

	protected:
		RGBColor color;

		GeometricObject&
		operator= (const GeometricObject& rhs);
};

inline void
GeometricObject::set_color(const RGBColor& c) {
	color = c;
}

inline void
GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

inline RGBColor
GeometricObject::get_color(void) {
	return (color);
}

#endif
