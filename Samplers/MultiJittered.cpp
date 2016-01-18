#include <cmath>
#include "Utilities/Math.h"
#include "MultiJittered.h"

MultiJittered::MultiJittered(const int n_samples) :Sampler(n_samples) {
	generateSamples();
}

MultiJittered::MultiJittered(const MultiJittered& mj) : Sampler(mj) {
	generateSamples();
}

MultiJittered* MultiJittered::clone(void) const {
	return new MultiJittered(*this);
}

void MultiJittered::generateSamples(void) {		
			
	int n = (int)sqrt((float)n_samples);
	float subcell_width = 1.0 / ((float) n_samples);
	
	Point2D fill_point;
	for (int j = 0; j < n_samples * n_sets; j++)
		samples.push_back(fill_point);
	
	for (int p = 0; p < n_sets; p++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				samples[i * n + j + p * n_samples].x = (i * n + j) * subcell_width + rand_float(0, subcell_width);
				samples[i * n + j + p * n_samples].y = (j * n + i) * subcell_width + rand_float(0, subcell_width);
			}
	
	for (int p = 0; p < n_sets; p++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				int k = rand_int(j, n - 1);
				float t = samples[i * n + j + p * n_samples].x;
				samples[i * n + j + p * n_samples].x = samples[i * n + k + p * n_samples].x;
				samples[i * n + k + p * n_samples].x = t;
			}
	
	for (int p = 0; p < n_sets; p++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				int k = rand_int(j, n - 1);
				float t = samples[j * n + i + p * n_samples].y;
				samples[j * n + i + p * n_samples].y = samples[k * n + i + p * n_samples].y;
				samples[k * n + i + p * n_samples].y = t;
		}
}


