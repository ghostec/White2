#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

int GUI(int argc, char* argv[]) {
  QApplication app(argc, argv);
  return app.exec();
}

int main(int argc, char *argv[]) {
  std::thread t(GUI, argc, argv);
  t.join();
  return 0;
}
