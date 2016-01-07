#ifndef __SERVER_WHITE_SERVER__
#define __SERVER_WHITE_SERVER__

#include <vector>
#include <string>
#include <QObject>
#include <QUdpSocket>
#include <QVector>
#include "Utilities/RGBColor.h"
#include "Message.h"

struct WorkerInfo {
  QHostAddress addr;
  quint16 port;
  int id;
  bool busy;

  explicit WorkerInfo(QHostAddress _addr, quint16 _port, int _id)
    : addr(_addr), port(_port), id(_id), busy(false) {};
};

struct ClientInfo {
  QHostAddress addr;
  quint16 port;
};

class Server : public QObject
{
  Q_OBJECT
public:
  explicit Server(QObject *parent = 0);
  void registerWorker(const WorkerInfo& _worker);
signals:
  void prepareJob(int wid);
  void jobCompleted(QDataStream& ds);
public slots:
  void readyRead();
  void sendFrame();
  void sendJob(int wid);
  void collectResult(QDataStream& ds);
private:
  int vres, hres;
  int cur_y, step;
  int received_pixels;
  QUdpSocket *socket;
  std::vector<WorkerInfo> workers;
  ClientInfo client;
  QVector<RGBColor> frame;
};

#endif