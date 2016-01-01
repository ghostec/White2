#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <memory>
#include "Utilities/RGBColor.h"
#include "GeometricObjects/Primitives/Sphere.h"
#include "Tracers/Tracer.h"
#include "Lights/Light.h"
#include "ViewPlane.h"

class World {
  public:
    ViewPlane vp;
    RGBColor background_color;
    std::vector<GeometricObject*> objects;
    std::unique_ptr<Tracer> tracer_ptr;
    Light* ambient_light;
    std::vector<Light*> lights;

    World(void);
    void build(void);
    void add_object(GeometricObject* object_ptr);
    void addLight(Light* light_ptr);
    ShadeRec hit_bare_bones_objects(const Ray& ray);
    ShadeRec hit_objects(const Ray& ray);
};

#endif
