#ifndef __BRDFS_BRDF__
#define __BRDFS_BRDF__

#include "Utilities/Constants.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Vector3D.h"
#include "Utilities/ShadeRec.h"
#include "Samplers/Sampler.h"

class BRDF {
protected:
  Sampler* sampler_ptr;
public:
  BRDF(void);
  void setSampler(Sampler* _sampler_ptr);
  virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
  virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
  virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
};

#endif
