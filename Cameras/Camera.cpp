#include "Camera.h"

Camera::Camera(MessageQueue<MessagePixel>& _mq) : mq(_mq) {}

void Camera::compute_uvw()
{
  w = eye - lookat;
  w.normalize();
  u = up ^ w;
  u.normalize();
  v = w ^ u;
}

const Point3D Camera::get_eye() const
{
  return eye;
}

const Point3D Camera::get_lookat() const
{
  return lookat;
}

void Camera::set_eye(const Point3D _eye)
{
  eye = _eye;
}

void Camera::set_lookat(const Point3D _lookat)
{
  lookat = _lookat;
}

void Camera::set_up(const Vector3D _up)
{
  up = _up;
}
