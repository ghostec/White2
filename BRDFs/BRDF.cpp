#include "BRDF.h"

BRDF::BRDF(void) : sampler_ptr(nullptr) {}

void BRDF::setSampler(Sampler * _sampler_ptr)
{
  sampler_ptr = _sampler_ptr;
  _sampler_ptr->mapSamplesToHemisphere(1);
}

RGBColor BRDF::f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi) const
{
  return black;
}

RGBColor BRDF::sample_f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi) const
{
  return black;
}

RGBColor BRDF::sample_f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi, float & pdf) const
{
  return black;
}

RGBColor BRDF::rho(const ShadeRec & sr, const Vector3D & wo) const
{
  return black;
}
