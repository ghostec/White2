#ifndef __LIGHTS_AMBIENT_OCCLUDER__
#define __LIGHTS_AMBIENT_OCCLUDER__

#include <vector>
#include "World/Settings.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Vector3D.h"
#include "Utilities/ShadeRec.h"
#include "Samplers/Sampler.h"
#include "Light.h"

struct AmbientOccluder_WorkerData {
  Vector3D u, v, w;
};

class AmbientOccluder : public Light {
private:
  float ls, min_amount;
  RGBColor color;
  std::vector<Sampler*> v_samplers;
  std::vector<AmbientOccluder_WorkerData> uvw;
public:
  AmbientOccluder(const Settings& s);
  void scaleRadiance(const float b);
  void setColor(const float c);
  void setColor(const RGBColor& c);
  void setColor(const float r, const float g, const float b);
  void setMinAmount(const float c);
  void setSampler(Sampler* _sampler_ptr);
  virtual Vector3D getDirection(ShadeRec& sr);
  virtual RGBColor L(ShadeRec& sr);
  virtual bool inShadow(const Ray& ray, const ShadeRec& sr) const;
};

#endif