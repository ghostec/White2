#ifndef __WHITE_MATH__
#define __WHITE_MATH__

#include <stdlib.h>
#include "Constants.h"

inline int rand_int() {
  return rand();
}

inline float rand_float() {
  return static_cast<float>(rand() * invRAND_MAX);
}

#endif
