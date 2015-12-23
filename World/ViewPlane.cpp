#include "Samplers/Jittered.h"
#include "Samplers/Regular.h"
#include "ViewPlane.h"

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

void ViewPlane::save_image() {
  FILE *f = fopen("image4.ppm", "w");
  fprintf(f, "P3\n%d %d\n%d\n", hres, vres, 255);
  for(int i = vres * vres - 1; i >= 0; i--)
    fprintf(f, "%d %d %d ", toInt(canvas[i].r), toInt(canvas[i].g), toInt(canvas[i].b));
}

void ViewPlane::set_num_samples(int _num_samples) {
  this->num_samples = _num_samples;
}

void ViewPlane::set_hres(int _hres) {
  this->hres = _hres;
}

void ViewPlane::set_vres(int _vres) {
  this->vres = _vres;
}

void ViewPlane::set_pixel_size(float _s) {
  this->s = _s;
}

void ViewPlane::set_gamma(float _gamma) {
  this->gamma = _gamma;
  this->inv_gamma = 1.0f/_gamma;
}

void ViewPlane::set_sampler(std::unique_ptr<Sampler> sp)
{
  num_samples = sp->get_num_samples();
  sampler_ptr = std::move(sp);
}

void ViewPlane::set_samples(const int num_samples)
{
  if(num_samples > 1) {
    sampler_ptr = std::unique_ptr<Jittered>(new Jittered(num_samples));
  }
  else {
    sampler_ptr = std::unique_ptr<Regular>(new Regular(1));
  }
}
