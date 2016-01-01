#include "Material.h"

Material::Material(void) {}

RGBColor Material::shade(ShadeRec & sr)
{
  return black;
}
