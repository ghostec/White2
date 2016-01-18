#ifndef __SAMPLERS_JITTERED__
#define __SAMPLERS_JITTERED__

#include <vector>
#include "Sampler.h"
#include "Utilities/Point2D.h"

class Jittered : public Sampler {
	public:
    Jittered(int _num_samples);
    Jittered(const Jittered& j);
    virtual Sampler* clone() const;
    virtual void generateSamples(void);
};

#endif
