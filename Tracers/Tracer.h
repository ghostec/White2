#ifndef __TRACER__
#define __TRACER__

#include "Utilities/Constants.h"
#include "Utilities/Ray.h"
#include "Utilities/RGBColor.h"

class World;

class Tracer {
	public:
		Tracer(void);
		Tracer(World* _world_ptr);
		virtual ~Tracer(void);
		virtual RGBColor trace_ray(const Ray& ray) const;
		virtual RGBColor trace_ray(const Ray ray, const int depth) const;
	protected:
		World* world_ptr;
};

#endif
