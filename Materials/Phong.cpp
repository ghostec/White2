#include "Phong.h"

Phong::Phong(void) : Material(), ambient_brdf(new Lambertian), diffuse_brdf(new Lambertian), specular_brdf(new GlossySpecular) {}

void Phong::setKa(const float k)
{
  ambient_brdf->setKd(k);
}

void Phong::setKd(const float k)
{
  diffuse_brdf->setKd(k);
}

void Phong::setCd(const RGBColor & c)
{
  ambient_brdf->setCd(c);
  diffuse_brdf->setCd(c);
}

void Phong::setCd(const float r, const float g, const float b)
{
  ambient_brdf->setCd(r, g, b);
  diffuse_brdf->setCd(r, g, b);
}

void Phong::setCd(const float c)
{
  ambient_brdf->setCd(c);
  diffuse_brdf->setCd(c);
}

void Phong::setKs(const float k)
{
  specular_brdf->setKs(k);
}

void Phong::setCs(const RGBColor & c)
{
  specular_brdf->setCs(c);
}

void Phong::setCs(const float r, const float g, const float b)
{
  specular_brdf->setCs(r, g, b);
}

void Phong::setCs(const float c)
{
  specular_brdf->setCs(c);
}

void Phong::setExp(const float _exp) {
  specular_brdf->setExp(_exp);
}

RGBColor Phong::shade(ShadeRec& sr)
{
  Vector3D wo = -sr.ray.d;
  RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_light->L(sr);
  int num_lights = sr.w.lights.size();

  for(int j = 0; j < num_lights; j++) {
    Vector3D wi = sr.w.lights[j]->getDirection(sr);
    float ndotwi = sr.normal * wi;

    if(ndotwi > 0.0) {
      L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi))
        * sr.w.lights[j]->L(sr) * ndotwi;
    }
  }

  return L;
}
