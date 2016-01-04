#ifndef __CAMERAS_CAMERA__
#define __CAMERAS_CAMERA__

#include "World/World.h"
#include "CameraWorker.h"

class Camera {
  private:
    CameraWorker* worker;
    int n_workers;
	public:
    Camera();
    void render(World& w);
    void setCameraWorker(CameraWorker* _worker);
};

#endif
