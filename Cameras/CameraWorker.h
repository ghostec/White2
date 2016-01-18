#ifndef __CAMERAS_CAMERAWORKER__
#define __CAMERAS_CAMERAWORKER__

#include "World/Settings.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"

class World;

class CameraWorker {
  protected:
    Point3D eye, lookat;
    Vector3D up, u, v, w;
    float exposure_time;
	public:
    CameraWorker();
    CameraWorker(const CameraWorker& _c);
    void computeUvw();
    virtual void render(int wid, Settings& s, World& w, int o_y, int e_y) = 0;
    virtual CameraWorker* clone() const = 0;
    const Point3D getEye() const;
    const Point3D getLookat() const;
    void setEye(const Point3D _eye);
    void setLookat(const Point3D _lookat);
    void setUp(const Vector3D _up);
};

#endif
