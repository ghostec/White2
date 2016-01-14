#include "Constants.h"
#include "ShadeRec.h"

ShadeRec::ShadeRec(World& wr)
  : wid(0),
  w(wr),
  hit_an_object(false),
  material_ptr(nullptr),
  hit_point(),
  local_hit_point(),
  normal(),
  ray(),
  dir(),
  color(black),
  t(0.0)
{}

ShadeRec::ShadeRec(const ShadeRec& sr)
  : wid(sr.wid),
  w(sr.w),
  hit_an_object(sr.hit_an_object),
  material_ptr(sr.material_ptr),
  hit_point(sr.hit_point),
  local_hit_point(sr.local_hit_point),
  normal(sr.normal),
  ray(sr.ray),
  dir(sr.dir),
  color(sr.color),
  t(sr.t)
{}

ShadeRec::~ShadeRec(void) {}
