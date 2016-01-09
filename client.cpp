#include <QApplication>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "Network/Client/Client.h"

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Client client(QHostAddress("192.168.2.118"), 1234);
  client.setup();
  client.registerSelf();
  client.gui.window.show();

  return app.exec();
}
