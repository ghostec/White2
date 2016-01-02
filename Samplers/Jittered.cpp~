#include <iostream>
#include "Jittered.h"
#include "Utilities/Math.h"

Jittered::Jittered(int _num_samples) : Sampler(_num_samples) {
  generate_samples();
}

void Jittered::generate_samples(void) {
  auto n = static_cast<int>(std::sqrt(static_cast<float>(num_samples)));
  for(auto p = 0; p < num_sets; p++) {
    for(auto j = 0; j < n; j++) {
      for(auto k = 0; k < n; k++) {
        Point2D sp((k + rand_float()) / n, (j + rand_float()) / n);
        samples.push_back(sp);
      }
    }
  }
}