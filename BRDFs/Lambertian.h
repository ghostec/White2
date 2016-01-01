#ifndef __BRDFS_LAMBERTIAN__
#define __BRDFS_LAMBERTIAN__

#include "BRDF.h"

class Lambertian : public BRDF {
private:
  float kd;
  RGBColor cd;
public:
  Lambertian(void);
  virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
  virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
  void setKd(float _kd);
  void setCd(const float r, const float g, const float b);
  void setCd(const float c);
  void setCd(const RGBColor& c);
};

#endif
