#ifndef __SAMPLERS_REGULAR__
#define __SAMPLERS_REGULAR__

#include <vector>
#include "Sampler.h"
#include "Utilities/Point2D.h"

class Regular : public Sampler {
	public:
    Regular(int _num_samples);
    virtual void generateSamples(void);
};

#endif
