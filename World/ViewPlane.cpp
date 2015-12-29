#include "Samplers/Jittered.h"
#include "Samplers/Regular.h"
#include "ViewPlane.h"

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

void ViewPlane::saveImage() {
  FILE *f = fopen("image4.ppm", "w");
  fprintf(f, "P3\n%d %d\n%d\n", hres, vres, 255);
  for(int i = vres * vres - 1; i >= 0; i--)
    fprintf(f, "%d %d %d ", toInt(canvas[i].r), toInt(canvas[i].g), toInt(canvas[i].b));
}

void ViewPlane::setNumSamples(int _num_samples) {
  num_samples = _num_samples;
}

void ViewPlane::setSize(int _hres, int _vres)
{
  hres = _hres;
  vres = _vres;
  canvas.resize(_hres * _vres);
}

void ViewPlane::setPixelSize(float _s) {
  s = _s;
}

void ViewPlane::setGamma(float _gamma) {
  gamma = _gamma;
  inv_gamma = 1.0f/_gamma;
}

void ViewPlane::setSampler(std::unique_ptr<Sampler> sp)
{
  num_samples = sp->get_num_samples();
  sampler_ptr = std::move(sp);
}

void ViewPlane::setSamples(const int num_samples)
{
  if(num_samples > 1) {
    sampler_ptr = std::unique_ptr<Jittered>(new Jittered(num_samples));
  }
  else {
    sampler_ptr = std::unique_ptr<Regular>(new Regular(1));
  }
}
