#ifndef __SAMPLERS_MULTIJITTERED__
#define __SAMPLERS_MULTIJITTERED__

#include "Sampler.h"

class MultiJittered: public Sampler {
public:
  MultiJittered(const int num_samples);
	MultiJittered(const MultiJittered& mj);
  virtual MultiJittered* clone(void) const;
private:
  virtual void generate_samples(void);
};

#endif

