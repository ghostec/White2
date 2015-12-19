#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

#include <memory>
#include "Samplers/Sampler.h"

class ViewPlane {
  public:
    int hres, vres;
    float s, gamma, inv_gamma;
    int num_samples;
    std::unique_ptr<Sampler> sampler_ptr;

    void set_num_samples(int _num_samples);
    void set_hres(int _hres);
    void set_vres(int _vres);
    void set_pixel_size(float _s);
    void set_gamma(float _gamma);
    void set_sampler(std::unique_ptr<Sampler> sp);
    void set_samples(const int num_samples);  
};

#endif
