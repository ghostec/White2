#include <cmath>
#include "GlossySpecular.h"

GlossySpecular::GlossySpecular(void) : BRDF(), ks(0.0), cs(0.0) {}

RGBColor GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
  RGBColor L;
  float ndotwi = sr.normal * wi;
  Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
  float rdotwo = r * wo;

  if(rdotwo > 0.0) {
    L = ks * pow(rdotwo, exp);
  }
  
  return L;
}

RGBColor GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const
{
  return black; // placeholder (ch 24)
}

RGBColor GlossySpecular::rho(const ShadeRec & sr, const Vector3D & wo) const
{
  return black;
}

void GlossySpecular::setKs(const float _ks)
{
  ks = _ks;
}

void GlossySpecular::setCs(const float r, const float g, const float b)
{
  cs = RGBColor(r, g, b);
}

void GlossySpecular::setCs(const float c)
{
  cs = RGBColor(c);
}

void GlossySpecular::setCs(const RGBColor& c)
{
  cs = c;
}

void GlossySpecular::setExp(const float _exp)
{
  exp = _exp;
}
