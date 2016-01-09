#include "Message.h"
#include <iostream>

qint32 ArrayToInt(QByteArray source)
{
  qint32 temp;
  QDataStream data(&source, QIODevice::ReadWrite);
  data >> temp;
  return temp;
}

QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
  //Avoid use of cast, this is the Qt way to serialize objects
  QByteArray temp;
  QDataStream data(&temp, QIODevice::ReadWrite);
  data << source;
  return temp;
}

QByteArray readMessage(QTcpSocket* socket, QByteArray* buffer, qint32* s) {
  qint32 size = *s;
  while(socket->bytesAvailable() > 0) {
    buffer->append(socket->readAll());
    while((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
    {
      if(size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
      {
        size = ArrayToInt(buffer->mid(0, 4));
        *s = size;
        buffer->remove(0, 4);
      }
      if(size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
      {
        QByteArray data = buffer->mid(0, size);
        buffer->remove(0, size);
        size = 0;
        *s = size;
        return data;
      }
    }
  }
  return QByteArray();
}

void writeMessage(QTcpSocket* socket, QByteArray& data)
{
  socket->write(IntToArray(data.size()));
  socket->write(data);
  socket->waitForBytesWritten();
}

void writeMessage(QTcpSocket* socket, QByteArray& data1, QByteArray& data2)
{
  socket->write(IntToArray(data1.size() + data2.size()));
  socket->write(data1);
  socket->write(data2);
  socket->waitForBytesWritten();
}

QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Message& m) {
  out << (quint32)m;
  return out;
}

QDataStream &operator>>(QDataStream& in, WhiteNetwork::Message& m) {
  in >> (quint32&)m;
  return in;
}

QDataStream &operator<<(QDataStream& out, const RGBColor& e) {
  out << e.r << e.g << e.b;
  return out;
}

QDataStream &operator>>(QDataStream& in, RGBColor& e) {
  float x, y, z;
  in >> x >> y >> z;
  e = RGBColor(x, y, z);
  return in;
}

QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Job& job) {
  out << job.by << job.ey;
  return out;
}

QDataStream &operator>>(QDataStream& in, WhiteNetwork::Job& job) {
  int by, ey;
  in >> by >> ey;
  job = { by, ey };
  return in;
}

QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Register& reg) {
  out << reg.addr << reg.port << reg.id;
  return out;
}

QDataStream &operator>>(QDataStream& in, WhiteNetwork::Register& reg) {
  QHostAddress addr;
  quint16 port;
  int id;
  in >> addr >> port >> id;
  reg = { addr, port, id };
  return in;
}