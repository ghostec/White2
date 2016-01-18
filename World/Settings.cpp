#include "Samplers/MultiJittered.h"
#include "Settings.h"

Settings::Settings() : n_workers(1) {
  v_samplers.resize(1);
  v_samplers[0] = new MultiJittered(64);
}

void Settings::setNWorkers(int n) {
  n_workers = n;
  v_samplers.resize(n);
  for(int i = 1; i < n_workers; i++) {
    v_samplers[i] = v_samplers[0]->clone();
  }
}

void Settings::setNSamples(int n) {
  n_samples = n;
  for(int i = 0; i < n_workers; i++) {
    v_samplers[i]->setNSamples(n);
  }
}

void Settings::setSampler(Sampler* sampler_ptr) {
  for(int i = 0; i < n_workers; i++) {
    delete v_samplers[i];
    v_samplers[i] = sampler_ptr->clone();
  }
}
