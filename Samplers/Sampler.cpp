#include <algorithm>
#include <cmath>
#include "Utilities/Math.h"
#include "Sampler.h"

Sampler::Sampler(int _n_samples) : n_samples(_n_samples), n_sets(83), count(0), jump(0) {
  samples.reserve(n_samples * n_sets);
  setupShuffledIndices();
}

Sampler::Sampler(const Sampler& s) :
  n_samples(s.n_samples),
  n_sets(s.n_sets),
  samples(s.samples),
  hemisphere_samples(s.hemisphere_samples),
  shuffled_indices(s.shuffled_indices),
  count(0), jump(0)
{}

void Sampler::mapSamplesToHemisphere(const float e)
{
  int size = samples.size();
  hemisphere_samples.reserve(n_samples * n_sets);

  for(int i = 0; i < size; i++) {
    float cos_phi = cos(2.0 * PI * samples[i].x);
    float sin_phi = sin(2.0 * PI * samples[i].x);
    float cos_theta = pow((1.0 - samples[i].y), 1.0 / (e + 1.0));
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    float pu = sin_theta * cos_phi;
    float pv = sin_theta * sin_phi;
    float pw = cos_theta;

    hemisphere_samples.push_back(Point3D(pu, pv, pw));
  }
}

int Sampler::getNSamples() const {
  return n_samples;
}

void Sampler::setNSamples(const int n) {
  n_samples = n;
  generateSamples();
  setupShuffledIndices();
}

int Sampler::getNSets() const {
  return n_sets;
}

void Sampler::setNSets(const int n) {
  n_sets = n;
  generateSamples();
  setupShuffledIndices();
}

Point2D Sampler::sampleUnitSquare(void)
{
  if(count % n_samples == 0) {
    jump = (rand_int() % n_sets) * n_samples;
  }

  return samples[jump + shuffled_indices[jump + count++ % n_samples]];
}

Point3D Sampler::sampleHemisphere(void) {
  if(count % n_samples == 0) {
    jump = (rand_int() % n_sets) * n_samples;
  }

  return hemisphere_samples[jump + shuffled_indices[jump + count++ % n_samples]];
}

void Sampler::setupShuffledIndices(void) {
  shuffled_indices.reserve(n_samples * n_sets);
  std::vector<int> indices;
  indices.reserve(n_samples);

  for(int i = 0; i < n_samples; i++) indices.push_back(i);

  for(int i = 0; i < n_sets; i++) {
    std::random_shuffle(begin(indices), end(indices));
    for(int j = 0; j < n_samples; j++) {
      shuffled_indices.push_back(indices[j]);
    }
  }
}