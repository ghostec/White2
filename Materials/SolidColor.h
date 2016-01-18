#ifndef __MATERIALS_SOLID_COLOR__
#define __MATERIALS_SOLID_COLOR__

#include "Utilities/RGBColor.h"
#include "Material.h"

class SolidColor : public Material {
private:
  RGBColor color;
public:
  SolidColor(void);
  void setColor(const float c);
  void setColor(const float r, const float g, const float b);
  void setColor(const RGBColor c);
  virtual RGBColor shade(ShadeRec& sr);
};

#endif
