#include <algorithm>
#include <iostream>
#include "Camera.h"

Camera::Camera() {
  n_workers = 8;
}

void Camera::render(World& w)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::vector<std::thread> w_threads;

  if(n_workers == 1) {
    worker->render(w, 0, 600);
  }
  else {
    auto vres = w.vp.vres;
    auto hres = w.vp.hres;
    std::vector<std::thread> w_threads;
    w_threads.reserve(n_workers);
    int step = vres / n_workers;
    int y = 0;
    for(int i = 0; i < n_workers; i++) {
      w_threads.push_back(std::move(std::thread(&CameraWorker::render, worker, std::ref(w), y, y+step)));
      y += step;
    }
    for(int i = 0; i < n_workers; i++) {
      w_threads[i].join();
    }
  }

  end = std::chrono::system_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

  w.vp.saveImage();
}

void Camera::setCameraWorker(const CameraWorker& _worker)
{
  worker = _worker.clone();
}