#ifndef __NETWORK_MESSAGE__
#define __NETWORK_MESSAGE__

#include <iostream>
#include <string>
#include <QVector>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDataStream>
#include "Utilities/RGBColor.h"

namespace WhiteNetwork {

enum class Message {
  Job, PixelsData, JobDone, RegisterClient, RegisterWorker, Setup, FrameSent
};

struct Job {
  int by, ey;
};

struct Register {
  QHostAddress addr;
  quint16 port;
  int id;
};

};

struct Buffer {
  QByteArray data;
  int size;
  bool has_size;
};

qint32 ArrayToInt(QByteArray source);
QByteArray IntToArray(qint32 source);

QByteArray readMessage(QTcpSocket* socket, QByteArray* buffer, qint32* s);
void writeMessage(QTcpSocket* socket, QByteArray& data);

QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Message& m);
QDataStream &operator>>(QDataStream& in, WhiteNetwork::Message& m);
QDataStream &operator<<(QDataStream& out, const RGBColor& e);
QDataStream &operator>>(QDataStream& in, RGBColor& e);
QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Job& e);
QDataStream &operator>>(QDataStream& in, WhiteNetwork::Job& e);
QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Register& e);
QDataStream &operator>>(QDataStream& in, WhiteNetwork::Register& e);

#endif
