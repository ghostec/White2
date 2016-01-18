#ifndef __SAMPLERS__
#define __SAMPLERS__

#include <vector>
#include "Utilities/Point2D.h"
#include "Utilities/Point3D.h"

class Sampler {
	public:
    Sampler(int _n_samples);
    Sampler(const Sampler& s);
    virtual Sampler* clone() const = 0;
    virtual void generateSamples(void) = 0;
    void mapSamplesToHemisphere(const float e);
    int getNSamples() const;
    void setNSamples(const int n);
    int getNSets() const;
    void setNSets(const int n);
    Point2D sampleUnitSquare(void);
    Point3D sampleHemisphere(void);
    void setupShuffledIndices(void);

  protected:
    int n_samples, n_sets;
    std::vector<Point2D> samples;
    std::vector<Point3D> hemisphere_samples;
    std::vector<int> shuffled_indices;
    int count;
    int jump;
};

#endif
