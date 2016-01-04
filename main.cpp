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

class QGUIWindow : public QWidget {
private:
  CameraWorker* cam_worker;
public:
  QGUIWindow(CameraWorker* _cam_worker);
protected:
  virtual void keyPressEvent(QKeyEvent *event);
};

QGUIWindow::QGUIWindow(CameraWorker* _cam_worker) : QWidget() {
  cam_worker = _cam_worker;
};

void QGUIWindow::keyPressEvent(QKeyEvent *event) {
  auto eye = cam_worker->getEye();
  Point3D add;
  float s = 1.0;
  if(event->key() == Qt::Key_W) {
    add = Point3D(0.0, 0.0, s);
  }
  else if(event->key() == Qt::Key_S) {
    add = Point3D(0.0, 0.0, -s);
  }
  else if(event->key() == Qt::Key_A) {
    add = Point3D(-s, 0, 0.0);
  }
  else if(event->key() == Qt::Key_D) {
    add = Point3D(s, 0, 0.0);
  }
  else if(event->key() == Qt::Key_Q) {
    add = Point3D(0.0, -s, 0.0);
  }
  else if(event->key() == Qt::Key_E) {
    add = Point3D(0.0, s, 0.0);
  }
  cam_worker->setEye(eye + add);
  cam_worker->computeUvw();
}

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

int GUI(int argc, char* argv[], World& w, CameraWorker* cam_worker) {
  QApplication app(argc, argv);
  const auto vres = w.vp.vres;
  const auto hres = w.vp.hres;

  QGUIWindow window(cam_worker);
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
  World w;
  w.build();

  Pinhole p;
  p.setEye(Point3D(0, 40, 50));
  p.setLookat(Point3D(0, 0, 0));
  p.setUp(Vector3D(0, 1, 0));
  p.d = 200;
  p.computeUvw();

  Camera cam;
  cam.setCameraWorker(&p);

  std::thread t(GUI, argc, argv, std::ref(w), &p);

  cam.render(w);

  t.join();

  return 0;
}
