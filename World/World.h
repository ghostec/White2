#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <memory>
#include "ViewPlane.h"
#include "Utilities/RGBColor.h"
#include "GeometricObjects/Primitives/Sphere.h"
#include "Tracers/Tracer.h"

class World {
  public:
    ViewPlane vp;
    RGBColor background_color;
    std::vector<GeometricObject*> objects;
    std::unique_ptr<Tracer> tracer_ptr;

    World(void);
    void build(void);
    void add_object(GeometricObject* object_ptr);
    ShadeRec hit_bare_bones_objects(const Ray& ray);
};

#endif
