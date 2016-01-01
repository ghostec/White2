#ifndef __LIGHTS_LIGHT__
#define __LIGHTS_LIGHT__

#include "Utilities/Ray.h"
#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Constants.h"

class ShadeRec;

class Light {
public:
  Light(void);
  virtual Vector3D getDirection(ShadeRec& sr) = 0;
  virtual RGBColor L(ShadeRec& sr);
};

#endif
