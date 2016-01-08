#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "World/World.h"
#include "Cameras/Camera.h"
#include "Cameras/Pinhole.h"
#include "World/Renderer.h"

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

int GUI(int argc, char* argv[], World& w) {
  QApplication app(argc, argv);
  const auto vres = w.vp.vres;
  const auto hres = w.vp.hres;

  QWidget window;
  window.resize(600, 600);
  window.show();

  QImage img = QImage(hres, vres, QImage::Format_RGB32);
  QLabel lbl;
  lbl.setParent(&window);

  std::chrono::time_point<std::chrono::system_clock> timer, time;
  timer = std::chrono::system_clock::now();

  auto& canvas = w.vp.canvas;
  
  while(true) {
    time = std::chrono::system_clock::now();
    if((time - timer).count() >= 16666) {
      for(int i = 0; i < hres; i++) {
        for(int j = 0; j < vres; j++) {
          QRgb rgb = qRgb(toInt(canvas[j*vres+i].r), toInt(canvas[j*vres + i].g), toInt(canvas[j*vres + i].b));
          img.setPixel(i, vres - j - 1, rgb);
        }
      }
      lbl.setPixmap(QPixmap::fromImage(img));
      lbl.setGeometry(0, 0, img.width(), img.height());
      lbl.show();
      
      app.processEvents();
      timer = time;
    }
  }
  std::cout << "done\n";
  return app.exec();
}

int main(int argc, char *argv[]) {
  Renderer r;

  std::thread t(GUI, argc, argv, std::ref(r.world));

  r.render(100, 200);

  t.join();

  return 0;
}
