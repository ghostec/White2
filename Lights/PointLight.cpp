#include "Ambient.h"
#include "PointLight.h"

PointLight::PointLight(void) : ls(1.0), color(1.0), location(0.0) {}

void PointLight::scaleRadiance(const float b)
{
  ls = b;
}

void PointLight::setColor(const float c)
{
  color = c;
}

void PointLight::setColor(const RGBColor & c)
{
  color = c;
}

void PointLight::setColor(const float r, const float g, const float b)
{
  color = RGBColor(r, g, b);
}

void PointLight::setLocation(Vector3D _location)
{
  location = _location;
}

Vector3D PointLight::getDirection(ShadeRec& sr)
{
  return (location - sr.hit_point).hat();
}

RGBColor PointLight::L(ShadeRec & sr)
{
  return ls * color;
}
