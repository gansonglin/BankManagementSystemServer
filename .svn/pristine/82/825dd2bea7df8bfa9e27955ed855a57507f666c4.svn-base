#pragma once

#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
	Q_OBJECT

public:
	TcpSocket(QObject *parent);
	~TcpSocket();
	public slots:
	void onReadyRead();
};
