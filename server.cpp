#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "Network/Server.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Server server(QHostAddress::LocalHost, 1234);
  return app.exec();
}
