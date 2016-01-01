#include "Constants.h"
#include "ShadeRec.h"

ShadeRec::ShadeRec(World& wr)
  : hit_an_object(false),
  material_ptr(nullptr),
  hit_point(),
  local_hit_point(),
  normal(),
  ray(),
  depth(0),
  dir(),
  color(black),
  t(0.0),
  u(0.0),
  v(0.0),
  w(wr)
{}

ShadeRec::ShadeRec(const ShadeRec& sr)
  : hit_an_object(sr.hit_an_object),
  material_ptr(sr.material_ptr),
  hit_point(sr.hit_point),
  local_hit_point(sr.local_hit_point),
  normal(sr.normal),
  ray(sr.ray),
  depth(sr.depth),
  dir(sr.dir),
  color(sr.color),
  t(sr.t),
  u(sr.u),
  v(sr.v),
  w(sr.w)
{}

ShadeRec::~ShadeRec(void) {}
