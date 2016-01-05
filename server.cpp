#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "Server/WhiteServer.h"

int GUI(int argc, char* argv[]) {
  QApplication app(argc, argv);
  return app.exec();
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  //std::thread t(GUI, argc, argv);
  WhiteServer server;
  server.start();
  //t.join();
  return app.exec();
}
