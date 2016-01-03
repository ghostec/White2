#ifndef __BRDFS_GLOSSYSPECULAR__
#define __BRDFS_GLOSSYSPECULAR__

#include "BRDF.h"

class GlossySpecular : public BRDF {
private:
  float ks, exp;
  RGBColor cs;
public:
  GlossySpecular(void);
  virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
  virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
  void setKs(const float _ks);
  void setCs(const float r, const float g, const float b);
  void setCs(const float c);
  void setCs(const RGBColor& c);
  void setExp(const float _exp);
};

#endif
