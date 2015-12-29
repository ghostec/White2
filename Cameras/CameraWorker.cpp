#include "CameraWorker.h"

CameraWorker::CameraWorker() {}

CameraWorker::CameraWorker(const CameraWorker& _c) :
  eye(_c.eye), lookat(_c.lookat), up(_c.up), exposure_time(_c.exposure_time)
{
  compute_uvw();
}

void CameraWorker::compute_uvw()
{
  w = eye - lookat;
  w.normalize();
  u = up ^ w;
  u.normalize();
  v = w ^ u;
}

const Point3D CameraWorker::get_eye() const
{
  return eye;
}

const Point3D CameraWorker::get_lookat() const
{
  return lookat;
}

void CameraWorker::set_eye(const Point3D _eye)
{
  eye = _eye;
}

void CameraWorker::set_lookat(const Point3D _lookat)
{
  lookat = _lookat;
}

void CameraWorker::set_up(const Vector3D _up)
{
  up = _up;
}
