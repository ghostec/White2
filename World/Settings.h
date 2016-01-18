#ifndef __RENDERER_SETTINGS__
#define __RENDERER_SETTINGS__

#include <vector>
#include "Samplers/Sampler.h"

class Settings {
public:
  int n_workers;
  int n_samples;
  int vres, hres;
  std::vector<Sampler*> v_samplers;

  Settings();
  void setNWorkers(int n);
  void setNSamples(int n);
  void setSampler(Sampler* sampler_ptr);
};

#endif
