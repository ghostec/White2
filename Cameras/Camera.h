#ifndef __CAMERAS_CAMERA__
#define __CAMERAS_CAMERA__

class World;

#include "World/Settings.h"
#include "CameraWorker.h"

class Camera {
  private:
    CameraWorker* worker;
	public:
    Camera();
    void render(Settings& s, World& w, int by, int ey);
    void setCameraWorker(CameraWorker* _worker);
    CameraWorker* getCameraWorker();
};

#endif
