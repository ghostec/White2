#ifndef __SAMPLERS__
#define __SAMPLERS__

#include <vector>
#include "Utilities/Point2D.h"
#include "Utilities/Point3D.h"

class Sampler {
	public:
    Sampler(int _num_samples);
    Sampler(const Sampler& s);
    virtual Sampler* clone() const = 0;
    virtual void generate_samples(void) = 0;
    void mapSamplesToHemisphere(const float e);
    int get_num_samples() const;
    void set_num_samples(const int _num_samples);
    int get_num_sets() const;
    void set_num_sets(const int _num_sets);
    Point2D sample_unit_square(void);
    Point3D sample_hemisphere(void);
    void setup_shuffled_indices(void);

  protected:
    int num_samples, num_sets;
    std::vector<Point2D> samples;
    std::vector<Point3D> hemisphere_samples;
    std::vector<int> shuffled_indices;
    int count;
    int jump;
};

#endif
