#include "Ambient.h"

Ambient::Ambient(void) : Light(), ls(1.0), color(1.0) {}

void Ambient::scaleRadiance(const float b)
{
  ls = b;
}

void Ambient::setColor(const float c)
{
  color = RGBColor(c);
}

void Ambient::setColor(const RGBColor & c)
{
  color = c;
}

void Ambient::setColor(const float r, const float g, const float b)
{
  color = RGBColor(r, g, b);
}

Vector3D Ambient::getDirection(ShadeRec& sr)
{
  return Vector3D(0.0);
}

RGBColor Ambient::L(ShadeRec& sr)
{
  return ls * color;
}

bool Ambient::inShadow(const Ray& ray, const ShadeRec& sr) const {
  return false;
}