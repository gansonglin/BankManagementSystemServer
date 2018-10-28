#pragma once

#include <QTcpServer>

class TcpServer : public QTcpServer
{
	Q_OBJECT

public:
	TcpServer(QObject *parent = Q_NULLPTR);
	~TcpServer();
protected:
	virtual void incomingConnection(qintptr handle) override;
};
