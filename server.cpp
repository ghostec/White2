#include <QCoreApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "Network/Server/Server.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  Server server(QHostAddress("172.31.34.178"), 1234);
  return app.exec();
}
