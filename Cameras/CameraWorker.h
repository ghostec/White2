#ifndef __CAMERAS_CAMERAWORKER__
#define __CAMERAS_CAMERAWORKER__

#include "World/World.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"

class CameraWorker {
  protected:
    Point3D eye, lookat;
    Vector3D up, u, v, w;
    float exposure_time;
	public:
    CameraWorker();
    CameraWorker(const CameraWorker& _c);
    void compute_uvw();
    virtual void render_scene(World& w, int o_y, int e_y) = 0;
    virtual CameraWorker* clone() const = 0;
    const Point3D get_eye() const;
    const Point3D get_lookat() const;
    void set_eye(const Point3D _eye);
    void set_lookat(const Point3D _lookat);
    void set_up(const Vector3D _up);
};

#endif
