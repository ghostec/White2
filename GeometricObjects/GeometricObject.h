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

class Material;

class GeometricObject {
	public:
		GeometricObject(void);
		GeometricObject(const GeometricObject& object);
		virtual GeometricObject* clone(void) const = 0;
    virtual ~GeometricObject(void);
    virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
    void set_color(const RGBColor& c);
		void set_color(const float r, const float g, const float b);
		RGBColor get_color(void);
		virtual void add_object(GeometricObject* object_ptr);
		virtual Point3D sample(void);
		virtual float pdf(ShadeRec& sr);
		virtual Normal get_normal(void) const;
    virtual Normal get_normal(const Point3D& p);
    void setMaterial(Material* _material_ptr);
    Material* getMaterial(void) const;
	protected:
		RGBColor color;
    Material* material_ptr;
		GeometricObject& operator= (const GeometricObject& rhs);
};

inline void GeometricObject::set_color(const RGBColor& c) {
	color = c;
}

inline void GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

inline RGBColor GeometricObject::get_color(void) {
	return (color);
}

#endif
