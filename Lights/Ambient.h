#ifndef __LIGHTS_AMBIENT__
#define __LIGHTS_AMBIENT__

#include "Light.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Vector3D.h"

class Ambient : public Light {
private:
  float ls;
  RGBColor color;
public:
  Ambient(void);
  void scaleRadiance(const float b);
  void setColor(const float c);
  void setColor(const RGBColor& c);
  void setColor(const float r, const float g, const float b);
  virtual Vector3D getDirection(ShadeRec& sr);
  virtual RGBColor L(ShadeRec& sr);
};

#endif
