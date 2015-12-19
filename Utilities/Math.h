#ifndef __MATH__
#define __MATH__

#include <stdlib.h>
#include "Constants.h"

float rand_float() {
  return static_cast<float>(rand() * invRAND_MAX);
}

#endif
