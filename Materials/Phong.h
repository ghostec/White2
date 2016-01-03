#ifndef __MATERIALS_PHONG__
#define __MATERIALS_PHONG__

#include "BRDFs/Lambertian.h"
#include "BRDFs/GlossySpecular.h"
#include "Material.h"

class Phong : public Material {
private:
  Lambertian *ambient_brdf, *diffuse_brdf;
  GlossySpecular* specular_brdf;
public:
  Phong(void);
  void setKa(const float k);
  void setKd(const float k);
  void setCd(const RGBColor& c);
  void setCd(const float r, const float g, const float b);
  void setCd(const float c);
  void setKs(const float k);
  void setCs(const RGBColor& c);
  void setCs(const float r, const float g, const float b);
  void setCs(const float c);
  void setExp(const float _exp);
  virtual RGBColor shade(ShadeRec& sr);
};

#endif
