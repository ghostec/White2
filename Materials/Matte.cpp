#include "Matte.h"

Matte::Matte(void) : Material(), ambient_brdf(new Lambertian), diffuse_brdf(new Lambertian) {}

void Matte::setKa(const float k)
{
  ambient_brdf->setKd(k);
}

void Matte::setKd(const float k)
{
  diffuse_brdf->setKd(k);
}

void Matte::setCd(const RGBColor & c)
{
  ambient_brdf->setCd(c);
  diffuse_brdf->setCd(c);
}

void Matte::setCd(const float r, const float g, const float b)
{
  ambient_brdf->setCd(r, g, b);
  diffuse_brdf->setCd(r, g, b);
}

void Matte::setCd(const float c)
{
  ambient_brdf->setCd(c);
  diffuse_brdf->setCd(c);
}

RGBColor Matte::shade(ShadeRec& sr)
{
  Vector3D wo = -sr.ray.d;
  RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_light->L(sr);
  int num_lights = sr.w.lights.size();

  for(int j = 0; j < num_lights; j++) {
    Vector3D wi = sr.w.lights[j]->getDirection(sr);
    float ndotwi = sr.normal * wi;

    if(ndotwi > 0.0) {
      L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
    }
  }

  return L;
}
