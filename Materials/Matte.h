#ifndef __MATERIALS_MATTE__
#define __MATERIALS_MATTE__

#include "BRDFs/Lambertian.h"
#include "Material.h"

class Matte : public Material {
private:
  Lambertian *ambient_brdf, *diffuse_brdf;
public:
  Matte(void);
  void setKa(const float k);
  void setKd(const float k);
  void setCd(const RGBColor& c);
  void setCd(const float r, const float g, const float b);
  void setCd(const float c);
  virtual RGBColor shade(ShadeRec& sr);
};

#endif
