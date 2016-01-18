#ifndef __SHADE_REC__
#define __SHADE_REC__

#include "Point3D.h"
#include "Vector3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class Material;
class World;

class ShadeRec {
	public:
    int wid;
    World& w;
		bool hit_an_object;
    Material* material_ptr;
		Point3D hit_point;
		Point3D local_hit_point;
		Normal normal;
		Ray ray;
		RGBColor color;
		double t;

		ShadeRec(World& wr);
		ShadeRec(const ShadeRec& sr);
		~ShadeRec(void);
};

#endif
