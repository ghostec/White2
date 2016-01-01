#include <algorithm>
#include "Utilities/Math.h"
#include "Sampler.h"

Sampler::Sampler(int _num_samples) : num_samples(_num_samples), num_sets(83), count(0), jump(0) {
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}

void Sampler::mapSamplesToHemisphere(const float e)
{
  int size = samples.size();
  hemisphere_samples.reserve(num_samples * num_sets);

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

int Sampler::get_num_samples() const {
  return num_samples;
}

void Sampler::set_num_samples(const int _num_samples) {
  num_samples = _num_samples;
}

int Sampler::get_num_sets() const {
  return num_sets;
}

void Sampler::set_num_sets(const int _num_sets) {
  num_sets = _num_sets;
}

Point2D Sampler::sample_unit_square(void)
{
  if(count % num_samples == 0) {
    jump = (rand_int() % num_sets) * num_samples;
  }

  return samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

Point3D Sampler::sample_hemisphere(void) {
  if(count % num_samples == 0) {
    jump = (rand_int() % num_sets) * num_samples;
  }

  return hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

void Sampler::setup_shuffled_indices(void) {
  shuffled_indices.reserve(num_samples * num_sets);
  std::vector<int> indices;
  indices.reserve(num_samples);

  for(int i = 0; i < num_samples; i++) indices.push_back(i);

  for(int i = 0; i < num_sets; i++) {
    std::random_shuffle(begin(indices), end(indices));
    for(int j = 0; j < num_samples; j++) {
      shuffled_indices.push_back(indices[j]);
    }
  }
}