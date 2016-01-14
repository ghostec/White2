#ifndef __CAMERAS_PINHOLE__
#define __CAMERAS_PINHOLE__

#include "Utilities/Point2D.h"
#include "World/World.h"
#include "World/Settings.h"
#include "CameraWorker.h"

class Pinhole : public CameraWorker {
  private:
  public:
    Pinhole();
    Pinhole(const Pinhole& _p);
    virtual CameraWorker* clone() const;
    float d, zoom;
    Vector3D rayDirection(const Point2D& p);
    void render(int wid, Settings& s, World& w, int o_y, int e_y);
};

#endif
