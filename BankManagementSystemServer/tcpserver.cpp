#include <QDebug>

#include "tcpserver.h"
#include "tcpsocket.h"

TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent)
{
	this->listen(QHostAddress::Any, 8080);
	qDebug() <<QStringLiteral("8080监听成功...");
}

TcpServer::~TcpServer()
{
}

void TcpServer::incomingConnection(qintptr handle)
{
	TcpSocket *socket = new TcpSocket(this);
	if (!socket->setSocketDescriptor(handle))
	{
		qDebug() << "setSocketDescriptor is failure...";
		return;
	}
	QString str = socket->peerAddress().toString();
	quint16 port = socket->peerPort();
	qDebug() << "用户" << str << ":"<<"port:"<<QString::number(port) <<QStringLiteral("已连接....");
}
