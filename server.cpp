#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "Network/Server/Server.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Server server(QHostAddress("192.168.2.118"), 1234);
  return app.exec();
}
