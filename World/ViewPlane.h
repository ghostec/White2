#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

#include <memory>
#include <vector>
#include "Samplers/Sampler.h"
#include "Utilities/RGBColor.h"

class ViewPlane {
  public:
    int hres, vres;
    float s, gamma, inv_gamma;
    std::vector<RGBColor> canvas;

    void setSize(int _hres, int _vres);
    void setPixelSize(float _s);
    void setGamma(float _gamma);
    void saveImage();
};

#endif
