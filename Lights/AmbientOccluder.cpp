#include <algorithm>
#include <iostream>
#include "World/World.h"
#include "Samplers/Regular.h"
#include "Samplers/Jittered.h"
#include "Samplers/MultiJittered.h"
#include "AmbientOccluder.h"

AmbientOccluder::AmbientOccluder(const Settings& s) : Light(), ls(1.0), color(1.0), min_amount(0.25) {
  auto sampler_ptr = new MultiJittered(s.n_samples);
  sampler_ptr->mapSamplesToHemisphere(1);
  v_samplers.resize(s.n_workers);
  for(int i = 0; i < s.n_workers; i++) {
    v_samplers[i] = sampler_ptr->clone();
  }
  uvw.resize(s.n_workers);
}

void AmbientOccluder::scaleRadiance(const float b)
{
  ls = b;
}

void AmbientOccluder::setColor(const float c)
{
  color = RGBColor(c);
}

void AmbientOccluder::setColor(const RGBColor & c)
{
  color = c;
}

void AmbientOccluder::setColor(const float r, const float g, const float b)
{
  color = RGBColor(r, g, b);
}

void AmbientOccluder::setMinAmount(const float c)
{
  min_amount = c;
}

void AmbientOccluder::setSampler(Sampler* sampler_ptr)
{
  sampler_ptr->mapSamplesToHemisphere(1);
  for(int i = 0; i < v_samplers.size(); i++) {
    delete v_samplers[i];
    v_samplers[i] = sampler_ptr->clone();
  }
}

Vector3D AmbientOccluder::getDirection(ShadeRec& sr)
{
  const auto& d = uvw[sr.wid];
  Point3D sp = v_samplers[sr.wid]->sampleHemisphere();
  return sp.x * d.u + sp.y * d.v + sp.z * d.w;
}

RGBColor AmbientOccluder::L(ShadeRec& sr)
{
  auto& d = uvw[sr.wid];
  d.w = sr.normal;
  // jitter up vector, in case normal is vertical
  d.v = d.w ^ Vector3D(0.0072, 1.0, 0.0034);
  d.v.normalize();
  d.u = d.v ^ d.w;
  Ray shadow_ray;
  shadow_ray.o = sr.hit_point;
  shadow_ray.d = getDirection(sr);

  if(inShadow(shadow_ray, sr)) {
    return min_amount * ls * color;
  }
  else {
    return ls * color;
  }
}

bool AmbientOccluder::inShadow(const Ray& ray, const ShadeRec& sr) const {
  double t;
  int n_objects = sr.w.objects.size();
  for(int i = 0; i < n_objects; i++) {
    if(sr.w.objects[i]->shadowHit(ray, t)) {
      return true;
    }
  }
  return false;
}