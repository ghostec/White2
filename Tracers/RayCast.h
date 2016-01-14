#ifndef __TRACERS_RAYCAST__
#define __TRACERS_RAYCAST__

#include "Tracer.h"

class RayCast : public Tracer {
	public:
    RayCast(void);
    RayCast(World* _world_ptr);
    virtual RGBColor trace_ray(const int wid, const Ray ray, const int depth) const;
};

#endif
