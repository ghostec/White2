#ifndef __CANVAS__
#define __CANVAS__

#include <mutex>
#include <condition_variable>
#include <vector>
#include "RGBColor.h"

class Canvas {
private:
  std::vector<RGBColor> v;
  int vres, hres;
  mutable std::mutex m;
  mutable std::condition_variable c;
public:
  Canvas();
  Canvas(const Canvas& canvas);
  Canvas(int _vres, int _hres);
  void setSize(int _vres, int _hres);
  void setPixel(int x, int y, const RGBColor col);
  void setPixmap(const std::vector<RGBColor> _v);
  const std::vector<RGBColor> get() const;
  int getVres() const;
  int getHres() const;
  Canvas operator+=(const Canvas& _canvas);
};

#endif
