#include "Canvas.h"

Canvas::Canvas() : vres(0), hres(0), v(), m(), c() {}

Canvas::Canvas(const Canvas & canvas) : vres(canvas.vres), hres(canvas.hres), v(canvas.v), m(), c() {}

Canvas::Canvas(int _vres, int _hres) : vres(_vres), hres(_hres), m(), c()
{
  v.resize(_vres * _hres);
}

void Canvas::setSize(int _vres, int _hres)
{
//  std::lock_guard<std::mutex> lock(m);
  vres = _vres;
  hres = _hres;
  v.resize(_vres * _hres);
//  c.notify_one();
}

void Canvas::setPixel(int x, int y, const RGBColor col)
{
  // x < hres? y < vres?
//  std::lock_guard<std::mutex> lock(m);
  v[vres*y + x] = col;
//  c.notify_one();
}

void Canvas::setPixmap(const std::vector<RGBColor> _v)
{
  v = _v;
}

const std::vector<RGBColor> Canvas::get() const
{
  std::unique_lock<std::mutex> lock(m);
//  c.wait(lock);
  const auto canvas = v;
  return std::move(canvas);
}

int Canvas::getVres() const
{
//  std::unique_lock<std::mutex> lock(m);
//  c.wait(lock);
  return vres;
}

int Canvas::getHres() const
{
//  std::unique_lock<std::mutex> lock(m);
//  c.wait(lock);
  return hres;
}

Canvas Canvas::operator+=(const Canvas & _canvas)
{
  const auto c = _canvas.get();
  v.insert(v.end(), c.begin(), c.end());
  return Canvas();
}
