#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include "World/World.h"
#include "Cameras/Pinhole.h"
#include "Utilities/MessageQueue.h"
#include "Utilities/MessagePixel.h"

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

int GUI(int argc, char* argv[], World& w, MessageQueue<MessagePixel>& mq) {
  QApplication app(argc, argv);
  const auto vres = w.vp.vres;
  const auto hres = w.vp.hres;
  QImage img = QImage(hres, vres, QImage::Format_RGB32);
  QLabel lbl;
  std::chrono::time_point<std::chrono::system_clock> timer, time;
  timer = std::chrono::system_clock::now();
  while(true) {
    if(!mq.empty()) {
      const auto m = mq.front(); mq.pop();
      if(m.type == MessagePixel_e::Done) {
        break;
      }
      QRgb v = qRgb(toInt(m.color.r), toInt(m.color.g), toInt(m.color.b));
      img.setPixel(m.x, vres - m.y - 1, v);
      time = std::chrono::system_clock::now();
      if((time - timer).count() >= 33000) {
        lbl.setPixmap(QPixmap::fromImage(img));
        lbl.setGeometry(200, 200, img.width(), img.height());
        lbl.show();
        app.processEvents(QEventLoop::ExcludeUserInputEvents);
        timer = time;
      }
      
    }
  }
  return app.exec();
}

int main(int argc, char *argv[]) {
  MessageQueue<MessagePixel> mq;
  World w;
  w.build();
  //w.render_perspective();
  Pinhole p(mq);
  p.set_eye(Point3D(0, 50, 60));
  p.set_lookat(Point3D(0, 0, 0));
  p.set_up(Vector3D(0, 1, 0));
  p.d = 200;
  p.compute_uvw();

  std::thread t1(&Pinhole::render_scene, p, std::ref(w));
  std::thread t2(GUI, argc, argv, std::ref(w), std::ref(mq));
  t1.join();
  t2.join();
  return 0;
}
