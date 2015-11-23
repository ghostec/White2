#include "ViewPlane.h"

void
ViewPlane::set_hres(int _hres) {
  this->hres = _hres;
}

void
ViewPlane::set_vres(int _vres) {
  this->vres = _vres;
}

void
ViewPlane::set_pixel_size(float _s) {
  this->s = _s;
}

void
ViewPlane::set_gamma(float _gamma) {
  this->gamma = _gamma;
  this->inv_gamma = 1.0f/_gamma;
}
