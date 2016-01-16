#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <QVector>
#include <QDataStream>
#include "Network/Message.h"
#include "Server.h"

Server::Server(QHostAddress addr, quint16 port, QObject *parent) : QObject(parent)
{
  server = new QTcpServer(this);

  connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
  connect(this, SIGNAL(dataReceived(QTcpSocket*, QByteArray)),
    this, SLOT(handleData(QTcpSocket*, QByteArray)));

  vres = hres = 600;
  frame.resize(vres * hres);
  frame.fill(RGBColor(1.0, 0.0, 0.0));

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
  qDebug() << "Send Job";

  WhiteNetwork::Job job = { cur_y, cur_y + step };
  cur_y += step;

  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds << WhiteNetwork::Message::Job << job;
  writeMessage(socket, data);
}

void Server::sendJobs()
{
  for(const auto socket : workers_sockets) {
    sendJob(socket);
  }
}

void Server::sendFrame()
{
  int start = 0;
  int k = 0;
  int n_pixels = vres*hres;

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
  ds >> start;
  end = start;
  
  // mutexes

    
  // STL insert/copy
  while(!ds.atEnd()) ds >> frame[end++];

  received_pixels += (end - start);
  if(received_pixels >= vres * hres) {
    std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;
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
    qDebug() << "Client";
    start_time = std::chrono::system_clock::now();
    sendJobs();
  }
  else if(type == WhiteNetwork::Message::RegisterWorker) {
    workers_sockets.push_back(socket);
    qDebug() << "Worker";
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
