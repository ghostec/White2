#include <cmath>
#include "Samplers/Jittered.h"
#include "Samplers/Regular.h"
#include "ViewPlane.h"

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

void ViewPlane::saveImage() {
  FILE *f = fopen("image10.ppm", "w");
  fprintf(f, "P3\n%d %d\n%d\n", hres, vres, 255);
  for(int i = 0; i < vres; i++) {
    for(int j = 0; j < hres; j++) {
      const auto p = hres*(vres-i-1) + j;
      fprintf(f, "%d %d %d ", toInt(canvas[p].r), toInt(canvas[p].g), toInt(canvas[p].b));
    }
  }
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