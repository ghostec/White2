#ifndef __SHADE_REC__
#define __SHADE_REC__

class World;

#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class ShadeRec {
	public:
		bool hit_an_object;
		Point3D hit_point;
		Point3D local_hit_point;
		Normal normal;
		Ray ray;
		int depth;
		RGBColor color;
		double t;
		float u;
		float v;
		World& w;

		ShadeRec(World& wr);
		ShadeRec(const ShadeRec& sr);
		~ShadeRec(void);
};

#endif
