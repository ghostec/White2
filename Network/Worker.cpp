#include <vector>
#include <iostream>
#include <QVector>
#include <QDataStream>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include "Message.h"
#include "Worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
  socket = new QUdpSocket(this);
  socket->bind(QHostAddress::LocalHost, 1236);

  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

  server_addr = QHostAddress::LocalHost;
  server_port = 1234;

  id = 0;
}

void Worker::setup() {
  vres = 600;
  hres = 600;
}

void Worker::work(WhiteNetwork::Job job)
{
  canvas.resize(hres*(job.ey - job.by));
  sendResult(job);
}

void Worker::sendResult(WhiteNetwork::Job job)
{
  int offset = job.by * hres;
  int start = offset;
  int k = 0;
  int n_pixels = (job.ey - job.by)*hres;

  while(k < n_pixels) {
    QByteArray _data;
    QDataStream _ds(&_data, QIODevice::ReadWrite);
    while(_data.size() < 500 && k < n_pixels) {
      _ds << canvas[k++];
    }
    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    ds << WhiteNetwork::Message::PixelsData << start << offset + k;
    ds.writeRawData(_data.data(), _data.size());
    start = offset + k;
    socket->writeDatagram(data, server_addr, server_port);
  }

  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds << WhiteNetwork::Message::JobDone << id;
  socket->writeDatagram(data, server_addr, server_port);
}

void Worker::registerSelf()
{
  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  WhiteNetwork::Register reg = {QHostAddress::LocalHost, 1236};
  ds << WhiteNetwork::Message::RegisterWorker << reg;
  socket->writeDatagram(data, server_addr, server_port);
}

void Worker::readyRead()
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

    if(type == WhiteNetwork::Message::Job) {
      WhiteNetwork::Job job;
      ds >> job;
      std::cout << "Received Job\n";
      work(job);
    }
    else if(type == WhiteNetwork::Message::Setup) {
      setup();
    }

  }
}