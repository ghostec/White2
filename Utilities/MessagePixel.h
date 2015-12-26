#ifndef __MESSAGE_PIXEL__
#define __MESSAGE_PIXEL__

#include "RGBColor.h"
#include "Point2D.h"

enum class MessagePixel_e {
  Pixel, Done
};

struct MessagePixel {
  MessagePixel_e type;
  int x, y;
  RGBColor color;
};

#endif