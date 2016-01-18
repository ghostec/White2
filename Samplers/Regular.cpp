#include <iostream>
#include <cmath>
#include "Regular.h"
#include "Utilities/Math.h"

Regular::Regular(int _num_samples) : Sampler(_num_samples) {
  generateSamples();
}

void Regular::generateSamples(void) {
  auto n = static_cast<int>(std::sqrt(static_cast<float>(n_samples)));
  for(auto p = 0; p < n_sets; p++) {
    for(auto j = 0; j < n; j++) {
      for(auto k = 0; k < n; k++) {
        Point2D sp((k + 0.5) / n, (j + 0.5) / n);
        samples.push_back(sp);
      }
    }
  }
}
