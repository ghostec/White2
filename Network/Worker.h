#ifndef __NETWORK_WORKER__
#define __NETWORK_WORKER__

#include <QObject>
#include <QTcpSocket>
#include <QVector>
#include "Utilities/RGBColor.h"
#include "Message.h"

class Worker : public QObject
{
  Q_OBJECT
public:
  explicit Worker(QHostAddress server_addr, quint16 server_port, QObject *parent = 0);
  void setup();
  void work(WhiteNetwork::Job job);
  void sendResult(WhiteNetwork::Job job);
  void registerSelf();
signals:
  void dataReceived(QTcpSocket* socket, QByteArray data);
public slots:
  void readyRead();
  void handleData(QTcpSocket* socket, QByteArray data);
private:
  QTcpSocket *socket;
  QByteArray* buffer;
  qint32* size;

  QVector<RGBColor> canvas;
  int vres, hres;
  int id;
};

#endif