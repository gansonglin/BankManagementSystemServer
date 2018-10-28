#include <QDebug>
#include <QtCore/QCoreApplication>

#include "tcpserver.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "main...";

	TcpServer * tcpServer = new TcpServer();

	return a.exec();
}
