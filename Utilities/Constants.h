#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <stdlib.h>
#include <limits>
#include "RGBColor.h"

const double 	PI = 3.1415926535897932384;
const double 	TWO_PI = 6.2831853071795864769;
const double 	PI_ON_180 = 0.0174532925199432957;
const double 	invPI = 0.3183098861837906715;
const double 	invTWO_PI = 0.1591549430918953358;

const double kEpsilon = 0.0001;
const double kMAX_DOUBLE = std::numeric_limits<double>::max();
const float kMAX_FLOAT = std::numeric_limits<float>::max();

const RGBColor black(0.0);
const RGBColor white(1.0);
const RGBColor red(1.0, 0.0, 0.0);

const float invRAND_MAX = 1.0 / static_cast<float>(RAND_MAX);

#endif
