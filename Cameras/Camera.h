#ifndef __CAMERAS_CAMERA__
#define __CAMERAS_CAMERA__

#include "World/World.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"

class Camera {
  protected:
    Point3D eye, lookat;
    Vector3D up, u, v, w;
    float exposure_time;
	public:
    Camera();
    void compute_uvw();
    virtual void render_scene(World& w) = 0;
    const Point3D get_eye() const;
    const Point3D get_lookat() const;
    void set_eye(const Point3D _eye);
    void set_lookat(const Point3D _lookat);
    void set_up(const Vector3D _up);
};

#endif
