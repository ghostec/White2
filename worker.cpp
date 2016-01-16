#include <QCoreApplication>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "Network/Worker/Worker.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  Worker worker(QHostAddress("172.31.34.178"), 1234);
  worker.setup();
  worker.registerSelf();
  return app.exec();
}
