#include <vector>
#include <iostream>
#include <QVector>
#include <QDataStream>
#include "Message.h"
#include "Server.h"

Server::Server(QObject *parent) : QObject(parent)
{
  socket = new QUdpSocket(this);
  socket->bind(QHostAddress::LocalHost, 1234);

  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(this, SIGNAL(jobCompleted(QDataStream&)), this,
    SLOT(collectResult(QDataStream&)));
  connect(this, SIGNAL(prepareJob(int)), this, SLOT(sendJob(int)));

  vres = hres = 600;
  frame.resize(vres * hres);

  client = {QHostAddress::LocalHost, 1235};

  cur_y = 0;
  step = 100;
  received_pixels = 0;
}

void Server::registerWorker(const WorkerInfo& _worker)
{
  workers.push_back(_worker);
  sendJob(_worker.id);
}

void Server::sendJob(int wid)
{
  // mutexes
  if(cur_y >= vres) return;

  std::cout << "Send Job\n";
  WhiteNetwork::Job job = { cur_y, cur_y + step };
  cur_y += step;

  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds << WhiteNetwork::Message::Job << job;
  socket->writeDatagram(data, workers[wid].addr, workers[wid].port);
}

void Server::sendFrame()
{
  int start = 0;
  int k = 0;
  int n_pixels = vres*hres;

  std::cout << "Send Frame\n";
  
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
    socket->writeDatagram(data, client.addr, client.port);
  }

  QByteArray data;
  QDataStream ds(&data, QIODevice::ReadWrite);
  ds << WhiteNetwork::Message::FrameSent;
  socket->writeDatagram(data, client.addr, client.port);
}

void Server::collectResult(QDataStream& ds)
{
  int start, end;
  ds >> start >> end;
  received_pixels += (end - start);
  // mutexes

  // replace for stl copy insert
  for(int i = start; i < end; i++) {
    ds >> frame[i];
  }

  if(received_pixels >= 300000) {
    sendFrame();
  }
}

void Server::readyRead()
{
  while(socket->hasPendingDatagrams()) {
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort = 1235;

    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    WhiteNetwork::Message type;
    QDataStream ds(&buffer, QIODevice::ReadWrite);
    ds >> type;

    //qDebug() << "Message from: " << sender.toString();
    //qDebug() << "Message port: " << senderPort;

    if(type == WhiteNetwork::Message::RegisterWorker) {
      std::cout << "Register Worker\n";
      WhiteNetwork::Register reg;
      ds >> reg;
      WorkerInfo worker(reg.addr, reg.port, reg.id);
      registerWorker(worker);
    }
    else if(type == WhiteNetwork::Message::RegisterClient) {
      std::cout << "Register Client\n";
      WhiteNetwork::Register reg;
      ds >> reg;
      client.addr = reg.addr;
      client.port = reg.port;
    }
    else if(type == WhiteNetwork::Message::PixelsData) {
      emit jobCompleted(ds);
    }
    else if(type == WhiteNetwork::Message::JobDone) {
      int wid;
      std::cout << "Job Done\n";
      ds >> wid;
      emit prepareJob(wid);
    }
    
  }
}