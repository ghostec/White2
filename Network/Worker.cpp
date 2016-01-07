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
  socket = new QTcpSocket(this);
  buffer = new QByteArray();
  size = new qint32(0);

  server_addr = QHostAddress::LocalHost;
  server_port = 1234;

  socket->connectToHost(server_addr, server_port);

  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(this, SIGNAL(dataReceived(QTcpSocket*, QByteArray)),
    this, SLOT(handleData(QTcpSocket*, QByteArray)));

  id = 0;
}

void Worker::setup() {
  vres = 600;
  hres = 600;
}

void Worker::work(WhiteNetwork::Job job)
{
  std::cout << "work(Job)\n";
  std::cout << job.by << " " << job.ey << std::endl;
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
    writeMessage(socket, data);
  }

  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds << WhiteNetwork::Message::JobDone;
  writeMessage(socket, data);
}

void Worker::registerSelf()
{
  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds << WhiteNetwork::Message::RegisterWorker;
  writeMessage(socket, data);
}

void Worker::handleData(QTcpSocket* socket, QByteArray data) {
  WhiteNetwork::Message type;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds >> type;

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

void Worker::readyRead()
{
  qint32 s = *size;
  while(socket->bytesAvailable() > 0) {
    buffer->append(socket->readAll());
    while((s == 0 && buffer->size() >= 4) || (s > 0 && buffer->size() >= s)) //While can process data, process it
    {
      if(s == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
      {
        s = ArrayToInt(buffer->mid(0, 4));
        *size = s;
        buffer->remove(0, 4);
      }
      if(s > 0 && buffer->size() >= s) // If data has received completely, then emit our SIGNAL with the data
      {
        QByteArray data = buffer->mid(0, s);
        buffer->remove(0, s);
        s = 0;
        *size = s;
        emit dataReceived(socket, data);
      }
    }
  }
}