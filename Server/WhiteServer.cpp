#include <vector>
#include <iostream>
#include <QVector>
#include <QDataStream>
#include "WhiteServer.h"

QDataStream &operator<<(QDataStream& out, const Vector3D& e) {
  out << e.x << e.y << e.z;
  return out;
}

QDataStream &operator>>(QDataStream& in, Vector3D& e) {
  double x, y, z;
  in >> x >> y >> z;
  e = Vector3D(x, y, z);
  return in;
}

WhiteServer::WhiteServer(QObject *parent) : QObject(parent)
{
  // create a QUDP socket
  socket = new QUdpSocket(this);

  // The most common way to use QUdpSocket class is 
  // to bind to an address and port using bind()
  // bool QAbstractSocket::bind(const QHostAddress & address, 
  //     quint16 port = 0, BindMode mode = DefaultForPlatform)
  socket->bind(QHostAddress::LocalHost, 1234);

  //connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void WhiteServer::HelloUDP()
{
  QByteArray Data;
  QVector<Vector3D> v = { Vector3D(1,2,3), Vector3D(4,4,4) };
  QDataStream ds(&Data, QIODevice::ReadWrite);
  ds << v;
  //Data.append("Hello from UDP");

  // Sends the datagram datagram 
  // to the host address and at port.
  // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram, 
  //                      const QHostAddress & host, quint16 port)
  socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
}

void WhiteServer::start()
{
  while(true) {
    while(socket->hasPendingDatagrams()) {
      // when data comes in
      QByteArray buffer;
      buffer.resize(socket->pendingDatagramSize());

      QHostAddress sender;
      quint16 senderPort = 1235;

      // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize, 
      //                 QHostAddress * address = 0, quint16 * port = 0)
      // Receives a datagram no larger than maxSize bytes and stores it in data. 
      // The sender's host address and port is stored in *address and *port 
      // (unless the pointers are 0).

      socket->readDatagram(buffer.data(), buffer.size(),
        &sender, &senderPort);

      QVector<Vector3D> v;
      QDataStream ds(&buffer, QIODevice::ReadWrite);
      ds >> v;
      Vector3D e = v[1];

      qDebug() << "Message from: " << sender.toString();
      qDebug() << "Message port: " << senderPort;
      qDebug() << "Message: " << e.x << " " << e.y << " " << e.z << "\n";
    }
  }
  std::cout << "SAIU\n";
}