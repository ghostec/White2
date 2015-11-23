#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.h"

class MultipleObjects: public Tracer {
	public:
		MultipleObjects(void);
		MultipleObjects(World* _worldPtr);

		virtual
		~MultipleObjects(void);

		virtual RGBColor
		trace_ray(const Ray& ray) const;
};

#endif
