#include <vector>
#include <QVector>
#include <QDataStream>
#include "WhiteClient.h"

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

WhiteClient::WhiteClient(QObject *parent) : QObject(parent)
{
  // create a QUDP socket
  socket = new QUdpSocket(this);

  // The most common way to use QUdpSocket class is 
  // to bind to an address and port using bind()
  // bool QAbstractSocket::bind(const QHostAddress & address, 
  //     quint16 port = 0, BindMode mode = DefaultForPlatform)
  socket->bind(QHostAddress::LocalHost, 1235);

  //connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void WhiteClient::HelloUDP()
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