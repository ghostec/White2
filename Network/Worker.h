#ifndef __NETWORK_WORKER__
#define __NETWORK_WORKER__

#include <QObject>
#include <QUdpSocket>
#include <QVector>
#include "Utilities/RGBColor.h"
#include "Message.h"

class Worker : public QObject
{
  Q_OBJECT
public:
  explicit Worker(QObject *parent = 0);
  void setup();
  void work(WhiteNetwork::Job job);
  void sendResult(WhiteNetwork::Job job);
  void registerSelf();
signals:
public slots:
  void readyRead();
private:
  QUdpSocket *socket;
  QHostAddress server_addr;
  quint16 server_port;

  QVector<RGBColor> canvas;
  int vres, hres;
  int id;
};

#endif