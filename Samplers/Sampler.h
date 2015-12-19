#ifndef __SAMPLERS__
#define __SAMPLERS__

#include <vector>
#include "Utilities/Point2D.h"

class Sampler {
	public:
    Sampler(int _num_samples);
    virtual void generate_samples(void) = 0;
    int get_num_samples() const;
    void set_num_samples(const int _num_samples);
    int get_num_sets() const;
    void set_num_sets(const int _num_sets);
    Point2D sample_unit_square(void);
    void setup_shuffled_indices(void);

  protected:
    int num_samples, num_sets;
    std::vector<Point2D> samples;
    std::vector<int> shuffled_indices;
    int count;
    int jump;
};

#endif
