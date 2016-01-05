#ifndef __SERVER_WHITE_SERVER__
#define __SERVER_WHITE_SERVER__

#include <QObject>
#include <QtNetwork\QUdpSocket>
#include "Utilities/Vector3D.h"

class WhiteServer : public QObject
{
  Q_OBJECT
public:
  explicit WhiteServer(QObject *parent = 0);
  void HelloUDP();
  void start();
private:
  QUdpSocket *socket;
};

#endif