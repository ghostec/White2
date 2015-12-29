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
    void render_scene(World& w);
    void setCameraWorker(const CameraWorker& _worker);
};

#endif
