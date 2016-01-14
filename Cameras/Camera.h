#ifndef __CAMERAS_CAMERA__
#define __CAMERAS_CAMERA__

#include "World/World.h"
#include "World/Settings.h"
#include "CameraWorker.h"

class Camera {
  private:
    CameraWorker* worker;
	public:
    Camera();
    void render(Settings& s, World& w, int by, int ey);
    void setCameraWorker(CameraWorker* _worker);
    void setNWorkers(int _n_workers);
};

#endif
