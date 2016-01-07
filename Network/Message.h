#ifndef __NETWORK__
#define __NETWORK__

#include <string>
#include <QVector>
#include <QHostAddress>
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

QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Message& m);
QDataStream &operator>>(QDataStream& in, WhiteNetwork::Message& m);
QDataStream &operator<<(QDataStream& out, const RGBColor& e);
QDataStream &operator>>(QDataStream& in, RGBColor& e);
QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Job& e);
QDataStream &operator>>(QDataStream& in, WhiteNetwork::Job& e);
QDataStream &operator<<(QDataStream& out, const WhiteNetwork::Register& e);
QDataStream &operator>>(QDataStream& in, WhiteNetwork::Register& e);

#endif
