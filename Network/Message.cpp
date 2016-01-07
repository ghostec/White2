#include "Message.h"
#include <iostream>

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