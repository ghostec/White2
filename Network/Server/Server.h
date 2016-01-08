#ifndef __SERVER_WHITE_SERVER__
#define __SERVER_WHITE_SERVER__

#include <vector>
#include <string>
#include <chrono>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHash>
#include <QVector>
#include "Utilities/RGBColor.h"
#include "Network/Message.h"

class Server : public QObject
{
  Q_OBJECT
public:
  explicit Server(QHostAddress addr, quint16 port, QObject *parent = 0);
signals:
  void dataReceived(QTcpSocket* socket, QByteArray data);
public slots:
  void readyRead();
  void sendFrame();
  void sendJob(QTcpSocket* socket);
  void sendJobs();
  void collectResult(QDataStream& ds);
  void newConnection();
  void handleData(QTcpSocket* socket, QByteArray data);
private:
  QHash<QTcpSocket*, QByteArray*> buffers;
  QHash<QTcpSocket*, qint32*> sizes;
  QTcpSocket* client_socket;
  QVector<QTcpSocket*> workers_sockets;
  int vres, hres;
  int cur_y, step;
  int received_pixels;
  QTcpServer* server;
  QVector<RGBColor> frame;

  std::chrono::system_clock::time_point start_time;
};

#endif