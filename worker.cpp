#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "Network/Worker/Worker.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Worker worker(QHostAddress("192.168.2.118"), 1234);
  worker.setup();
  worker.registerSelf();
  return app.exec();
}
