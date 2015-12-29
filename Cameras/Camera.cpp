#include <algorithm>
#include <iostream>
#include "Camera.h"

Camera::Camera() {
  n_workers = 1;
  workers.resize(n_workers);
}

void Camera::render_scene(World & w)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::vector<std::thread> w_threads;

  if(n_workers == 1) {
    workers[0]->render_scene(0, w, 0, 0, w.vp.hres, w.vp.vres);
  }
  else {
    std::size_t h_workers = n_workers / 2;
    auto vres = w.vp.vres;
    auto hres = w.vp.hres;
    std::vector<std::thread> w_threads;
    w_threads.reserve(n_workers);
    int o_x, o_y, e_x, e_y;
    for(int i = 0; i < n_workers; i++) {
      if(i < h_workers) {
        o_x = i*hres / h_workers;
        o_y = 0;
        e_x = (i + 1)*hres / h_workers;
        e_y = vres / 2;
      }
      else {
        o_x = (i - h_workers)*hres / h_workers;
        o_y = vres / 2;
        e_x = (i - h_workers + 1)*hres / h_workers;
        e_y = vres;
      }
      w_threads.push_back(std::thread(&CameraWorker::render_scene, workers[i], i, std::ref(w), o_x, o_y, e_x, e_y));
    }
    for(int i = 0; i < n_workers; i++) {
      w_threads[i].join();
    }
  }

  end = std::chrono::system_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}

void Camera::setCameraWorker(const CameraWorker& _w)
{
  for(int i = 0; i < n_workers; i++) {
    workers[i] = _w.clone();
  }
}

const Canvas Camera::getCanvas() const
{
  if(n_workers == 1) return workers[0]->getCanvas();
  else {
    std::vector<RGBColor> v;
    v.resize(600 * 600);
    int h_workers = n_workers / 2;
    int hres = 600;
    int vres = 600;
    int w_hres = 600 / h_workers;
    int w_vres = 600 / 2;
    int k = 0;
    for_each(begin(workers), end(workers), [&](CameraWorker* w) {
      const auto _canvas = w->getCanvas().get();
      const int stride = (k < h_workers ? 0 : w_vres * hres);
      for(int i = 0; i < w_vres; i++) {
        for(int j = 0; j < w_hres; j++) {
            v[stride + i*hres + (k % h_workers)*w_hres + j] = _canvas[i*w_hres + j];
        }
      }
      k += 1;
    });
    Canvas canvas;
    canvas.setSize(600, 600); //resize cant work with insert
    canvas.setPixmap(v);
    canvas.setPixel(3, 3, white);
    return canvas;
  }
}
