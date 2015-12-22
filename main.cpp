#include <iostream>
#include "World/World.h"

int main() {
  World w;
  w.build();
  w.render_perspective();
  return 0;
}
