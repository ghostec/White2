#include <algorithm>
#include <iostream>
#include <thread>
#include "Camera.h"

Camera::Camera() {}

void Camera::render(Settings& s, World& w, int by, int ey)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  std::vector<std::thread> w_threads;

  if(s.n_workers == 1) {
    worker->render(0, s, w, by, ey);
  }
  else {
    auto vres = ey - by;
    auto hres = w.vp.hres;
    std::vector<std::thread> w_threads;
    w_threads.reserve(s.n_workers);
    int step = vres / s.n_workers;
    int y = by;
    for(int i = 0; i < s.n_workers; i++) {
      if(i == s.n_workers - 1 && y + step < ey) {
        step = ey - y;
      }
      w_threads.push_back(std::thread(&CameraWorker::render, worker, i, std::ref(s), std::ref(w), y, y+step));
      y += step;
    }
    
    for(int i = 0; i < s.n_workers; i++) {
     w_threads[i].join();
    }
    
  }

  end = std::chrono::system_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

  w.vp.saveImage();
}

void Camera::setCameraWorker(CameraWorker* _worker)
{
  worker = _worker;
}
