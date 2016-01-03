#ifndef __LIGHTS_POINTLIGHT__
#define __LIGHTS_POINTLIGHT__

#include "Light.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Vector3D.h"
#include "Utilities/ShadeRec.h"
#include "World/World.h"

class ShadeRec;

class PointLight : public Light {
private:
  float ls;
  RGBColor color;
  Point3D location;
public:
  PointLight(void);
  void scaleRadiance(const float b);
  void setColor(const float c);
  void setColor(const RGBColor& c);
  void setColor(const float r, const float g, const float b);
  void setLocation(Point3D _location);
  virtual Vector3D getDirection(ShadeRec& sr);
  virtual RGBColor L(ShadeRec& sr);
  virtual bool inShadow(const Ray& ray, const ShadeRec& sr) const;
};

#endif
