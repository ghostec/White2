#include "SolidColor.h"

SolidColor::SolidColor(void) : Material(), color(1.0) {}

void SolidColor::setColor(const float c) {
  color = RGBColor(c);
}

void SolidColor::setColor(const float r, const float g, const float b) {
  color = RGBColor(r, g, b);
}

void SolidColor::setColor(const RGBColor c) {
  color = c;
}

RGBColor SolidColor::shade(ShadeRec& sr)
{
  return color;
}
