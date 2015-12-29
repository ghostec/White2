#ifndef __CAMERAS_PINHOLE__
#define __CAMERAS_PINHOLE__

#include "Utilities/Point2D.h"
#include "World/World.h"
#include "CameraWorker.h"

class Pinhole : public CameraWorker {
  private:
  public:
    Pinhole();
    Pinhole(const Pinhole& _p);
    virtual CameraWorker* clone() const;
    float d, zoom;
    Vector3D ray_direction(const Point2D& p);
    void render_scene(int tid, World& w, int o_x, int o_y, int e_x, int e_y);
};

#endif
