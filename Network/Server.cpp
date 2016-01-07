#include <vector>
#include <iostream>
#include <QVector>
#include <QDataStream>
#include "Message.h"
#include "Server.h"

Server::Server(QHostAddress addr, quint16 port, QObject *parent) : QObject(parent)
{
  server = new QTcpServer(this);

  connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
  connect(this, SIGNAL(dataReceived(QTcpSocket*, QByteArray)),
    this, SLOT(handleData(QTcpSocket*, QByteArray)));

  vres = hres = 600;
  frame.resize(vres * hres);

  if(!server->listen(addr, port))
  {
    qDebug() << "Server could not start";
  }
  else
  {
    qDebug() << "Server started!";
  }

  cur_y = 0;
  step = 100;
  received_pixels = 0;
}

void Server::sendJob(QTcpSocket* socket)
{
  // mutexes
  if(cur_y >= vres) return;

  WhiteNetwork::Job job = { cur_y, cur_y + step };
  cur_y += step;

  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds << WhiteNetwork::Message::Job << job;
  writeMessage(socket, data);
}

void Server::sendFrame()
{
  int start = 0;
  int k = 0;
  int n_pixels = vres*hres;
  
  frame[1] = RGBColor(1);
  frame[2] = RGBColor(1);
  frame[3] = RGBColor(1);
  frame[4] = RGBColor(1);
  frame[5] = RGBColor(1);
  frame[6] = RGBColor(1);

  while(k < n_pixels) {
    QByteArray _data;
    QDataStream _ds(&_data, QIODevice::ReadWrite);
    while(_data.size() < 500 && k < n_pixels) {
      _ds << frame[k++];
    }
    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    ds << WhiteNetwork::Message::PixelsData << start << k;
    ds.writeRawData(_data.data(), _data.size());
    start = k;
    writeMessage(client_socket, data);
  }

  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds << WhiteNetwork::Message::FrameSent;
  writeMessage(client_socket, data);
}

void Server::collectResult(QDataStream& ds)
{
  int start, end;
  ds >> start >> end;
  received_pixels += (end - start);
  // mutexes

  // STL insert/copy
  for(int i = start; i < end; i++) {
    ds >> frame[i];
  }

  if(received_pixels >= vres * hres) {
    sendFrame();
  }
}

void Server::newConnection()
{
  while(server->hasPendingConnections()) {
    QTcpSocket* socket = server->nextPendingConnection();
    buffers[socket] = new QByteArray();
    sizes[socket] = new qint32(0);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  }
}

void Server::handleData(QTcpSocket* socket, QByteArray data) {
  QDataStream ds(&data, QIODevice::ReadWrite);

  WhiteNetwork::Message type;
  ds >> type;

  if(type == WhiteNetwork::Message::RegisterClient) {
    client_socket = socket;
  }
  else if(type == WhiteNetwork::Message::RegisterWorker) {
    sendJob(socket);
  }
  else if(type == WhiteNetwork::Message::PixelsData) {
    collectResult(ds);
  }
  else if(type == WhiteNetwork::Message::JobDone) {
    sendJob(socket);
  }
}

void Server::readyRead()
{
  QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
  QByteArray* buffer = buffers.value(socket);
  qint32* s = sizes.value(socket);
  qint32 size = *s;
  while(socket->bytesAvailable() > 0) {
    buffer->append(socket->readAll());
    while((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size))
    {
      if(size == 0 && buffer->size() >= 4)
      {
        size = ArrayToInt(buffer->mid(0, 4));
        *s = size;
        buffer->remove(0, 4);
      }
      if(size > 0 && buffer->size() >= size)
      {
        QByteArray data = buffer->mid(0, size);
        buffer->remove(0, size);
        size = 0;
        *s = size;
        emit dataReceived(socket, data);
      }
    }
  }
}