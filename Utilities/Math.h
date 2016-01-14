#ifndef __WHITE_MATH__
#define __WHITE_MATH__

#include <stdlib.h>
#include "Constants.h"

float rand_float(int l, float h);

inline int rand_int() {
  return rand();
}

inline int rand_int(int l, int h) {
  return ((int)(rand_float(0, h - l + 1) + l));
}

inline float rand_float() {
  return static_cast<float>(rand() * invRAND_MAX);
}

inline float rand_float(int l, float h) {
  return (rand_float() * (h - l) + l);
}

#endif
