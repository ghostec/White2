#ifndef __CAMERAS_PINHOLE__
#define __CAMERAS_PINHOLE__

#include "Utilities/Point2D.h"
#include "World/World.h"
#include "Camera.h"

class Pinhole : public Camera {
  private:
    
  public:
    float d, zoom;
    Vector3D ray_direction(const Point2D& p);
    virtual void render_scene(World& w);
};

#endif
