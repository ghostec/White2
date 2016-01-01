#ifndef __MATERIALS_MATERIAL__
#define __MATERIALS_MATERIAL__

#include "World/World.h"
#include "Utilities/RGBColor.h"
#include "Utilities/ShadeRec.h"
#include "Utilities/Constants.h"

class Material {
public:
  Material(void);
  virtual RGBColor shade(ShadeRec& sr);
};

#endif
