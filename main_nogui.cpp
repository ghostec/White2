#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "World/Renderer.h"

int main(int argc, char *argv[]) {
  Renderer r;
  r.render(0, 600);

  return 0;
}
