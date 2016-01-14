#include <iostream>
#include "RayCast.h"
#include "World/World.h"
#include "Utilities/ShadeRec.h"
#include "Materials/Material.h"

RayCast::RayCast(void) : Tracer() {}

RayCast::RayCast(World* _world_ptr) : Tracer(_world_ptr) {}

RGBColor RayCast::trace_ray(const int wid, const Ray ray, const int depth) const
{
  ShadeRec sr(world_ptr->hit_objects(ray));
  sr.wid = wid;

  if(sr.hit_an_object) {
    sr.ray = ray;
    return sr.material_ptr->shade(sr);
  }
  else {
    return world_ptr->background_color;
  }
}
