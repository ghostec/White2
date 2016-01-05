#ifndef __Client_WHITE_Client__
#define __Client_WHITE_Client__

#include <QObject>
#include <QtNetwork\QUdpSocket>
#include "Utilities/Vector3D.h"

class WhiteClient : public QObject
{
  Q_OBJECT
public:
  explicit WhiteClient(QObject *parent = 0);
  void HelloUDP();
private:
  QUdpSocket *socket;
};

#endif