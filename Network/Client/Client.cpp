#include <vector>
#include <iostream>
#include <QVector>
#include <QDataStream>
#include "Network/Message.h"
#include "Client.h"
#include <chrono>
#include <thread>

Client::Client(QHostAddress server_addr, quint16 server_port, QObject *parent) : QObject(parent)
{
  socket = new QTcpSocket(this);
  buffer = new QByteArray();
  size = new qint32(0);

  socket->connectToHost(server_addr, server_port);

  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(this, SIGNAL(frameReceived()), this, SLOT(refreshWindow()));
  connect(this, SIGNAL(dataReceived(QTcpSocket*, QByteArray)),
    this, SLOT(handleData(QTcpSocket*, QByteArray)));
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
  ds << WhiteNetwork::Message::RegisterClient;
  writeMessage(socket, data);
}

void Client::handleData(QTcpSocket * socket, QByteArray data)
{
  QDataStream ds(&data, QIODevice::ReadWrite);

  WhiteNetwork::Message type;
  ds >> type;

  if(type == WhiteNetwork::Message::PixelsData) {
    // STL async
    receivePixels(ds);
  }
  else if(type == WhiteNetwork::Message::FrameSent) {
    // STL async
    emit frameReceived();
  }
  else if(type == WhiteNetwork::Message::Setup) {
    setup();
  }
}

void Client::readyRead()
{
  qint32 s = *size;
  while(socket->bytesAvailable() > 0) {
    buffer->append(socket->readAll());
    while((s == 0 && buffer->size() >= 4) || (s > 0 && buffer->size() >= s))
    {
      if(s == 0 && buffer->size() >= 4)
      {
        s = ArrayToInt(buffer->mid(0, 4));
        *size = s;
        buffer->remove(0, 4);
      }
      if(s > 0 && buffer->size() >= s)
      {
        QByteArray data = buffer->mid(0, s);
        buffer->remove(0, s);
        s = 0;
        *size = s;
        // STL async
        emit dataReceived(socket, data);
      }
    }
  }
}