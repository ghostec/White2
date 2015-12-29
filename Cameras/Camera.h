#ifndef __CAMERAS_CAMERA__
#define __CAMERAS_CAMERA__

#include "Utilities/Canvas.h"
#include "World/World.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "CameraWorker.h"
#include "Pinhole.h"

class Camera {
  private:
    std::vector<CameraWorker*> workers;
    int n_workers;
    Canvas canvas;
	public:
    Camera();
    void render_scene(World& w);
    void setCameraWorker(const CameraWorker& _w);
    const Canvas getCanvas() const;
};

#endif
