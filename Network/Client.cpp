#include <vector>
#include <iostream>
#include <QVector>
#include <QDataStream>
#include "Message.h"
#include "Client.h"

Client::Client(QObject *parent) : QObject(parent)
{
  socket = new QUdpSocket(this);
  socket->bind(QHostAddress::LocalHost, 1235);

  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(this, SIGNAL(frameReceived()), this, SLOT(refreshWindow()));

  server_addr = QHostAddress::LocalHost;
  server_port = 1234;
}

void Client::setup() {
  auto vres = 600;
  auto hres = 600;
  gui.vres = vres;
  gui.hres = hres;
  gui.window.resize(hres, vres);
  gui.img = QImage(hres, vres, QImage::Format_RGB32);
  gui.lbl.setParent(&gui.window);
  gui.frame.resize(hres * vres);
}

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

void Client::refreshWindow() {
  auto vres = gui.vres;
  auto hres = gui.hres;
  auto& frame = gui.frame;
  for(int i = 0; i < hres; i++) {
    for(int j = 0; j < vres; j++) {
      QRgb rgb = qRgb(toInt(frame[j*vres + i].r), toInt(frame[j*vres + i].g), toInt(frame[j*vres + i].b));
      gui.img.setPixel(i, vres - j - 1, rgb);
    }
  }
  gui.lbl.setPixmap(QPixmap::fromImage(gui.img));
  gui.lbl.setGeometry(0, 0, gui.img.width(), gui.img.height());
  gui.lbl.show();
}

void Client::receivePixels(QDataStream& ds)
{
  int start, end;
  ds >> start >> end;

  // replace for stl copy insert
  for(int i = start; i < end; i++) {
    ds >> gui.frame[i];
  }
}

void Client::registerSelf()
{
  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  WhiteNetwork::Register reg = {QHostAddress::LocalHost, 1235};
  ds << WhiteNetwork::Message::RegisterClient << reg;
  socket->writeDatagram(data, server_addr, server_port);
}

void Client::readyRead()
{
  while(socket->hasPendingDatagrams()) {
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender = server_addr;
    quint16 senderPort = server_port;

    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    WhiteNetwork::Message type;
    QDataStream ds(&buffer, QIODevice::ReadWrite);
    ds >> type;

    //qDebug() << "Message from: " << sender.toString();
    //qDebug() << "Message port: " << senderPort;

    if(type == WhiteNetwork::Message::PixelsData) {
      receivePixels(ds);
    }
    else if(type == WhiteNetwork::Message::FrameSent) {
      std::cout << "Frame Sent\n";
      emit frameReceived();
    }
    else if(type == WhiteNetwork::Message::Setup) {
      setup();
    }

  }
}