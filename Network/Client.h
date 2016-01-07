#ifndef __NETWORK_CLIENT__
#define __NETWORK_CLIENT__

#include <QObject>
#include <QTcpSocket>
#include <QVector>
#include <QtGui>
#include <QLabel>
#include <QImage>
#include "Utilities/RGBColor.h"
#include "Message.h"

struct GUI {
  QWidget window;
  QImage img;
  QLabel lbl;
  int vres, hres;
  QVector<RGBColor> frame;
};

class Client : public QObject
{
  Q_OBJECT
public:
  explicit Client(QObject *parent = 0);
  void setup();
  void receivePixels(QDataStream& ds);
  void registerSelf();
  GUI gui;
signals:
  void frameReceived();
  void dataReceived(QTcpSocket* socket, QByteArray data);
public slots:
  void refreshWindow();
  void readyRead();
  void handleData(QTcpSocket* socket, QByteArray data);
private:
  QTcpSocket* socket;
  QByteArray* buffer;
  qint32* size;
  QHostAddress server_addr;
  quint16 server_port;
};

#endif