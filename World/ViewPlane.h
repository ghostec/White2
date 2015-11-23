#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

class ViewPlane {
  public:
    int hres, vres;
    float s, gamma, inv_gamma;

    void
    set_hres(int _hres);

    void
    set_vres(int _vres);

    void
    set_pixel_size(float _s);

    void
    set_gamma(float _gamma);
};

#endif
