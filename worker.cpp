#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "Network/Worker.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Worker worker;
  worker.setup();
  worker.registerSelf();
  return app.exec();
}
