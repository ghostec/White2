#ifndef __JITTERED__
#define __JITTERED__

#include <vector>
#include "Sampler.h"
#include "Utilities/Point2D.h"

class Jittered : public Sampler {
	public:
    Jittered(int _num_samples);
    virtual void generate_samples(void);
};

#endif
