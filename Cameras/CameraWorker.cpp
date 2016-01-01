#include "CameraWorker.h"

CameraWorker::CameraWorker() {}

CameraWorker::CameraWorker(const CameraWorker& _c) :
  eye(_c.eye), lookat(_c.lookat), up(_c.up), exposure_time(_c.exposure_time)
{
  computeUvw();
}

void CameraWorker::computeUvw()
{
  w = eye - lookat;
  w.normalize();
  u = up ^ w;
  u.normalize();
  v = w ^ u;
}

const Point3D CameraWorker::getEye() const
{
  return eye;
}

const Point3D CameraWorker::getLookat() const
{
  return lookat;
}

void CameraWorker::setEye(const Point3D _eye)
{
  eye = _eye;
}

void CameraWorker::setLookat(const Point3D _lookat)
{
  lookat = _lookat;
}

void CameraWorker::setUp(const Vector3D _up)
{
  up = _up;
}
