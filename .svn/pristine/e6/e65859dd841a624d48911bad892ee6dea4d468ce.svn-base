#include <QJsonParseError>
#include <QJsonObject>

#include "tcpsocket.h"
#include "jsonutil.h"

TcpSocket::TcpSocket(QObject *parent)
	: QTcpSocket(parent)
{
	bool check = connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	Q_ASSERT(check);
}

TcpSocket::~TcpSocket()
{
}

void TcpSocket::onReadyRead()
{
	int type = 0;
	QByteArray byteArray = readAll();
	QJsonParseError jsonParseError;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArray, &jsonParseError);
	//if (jsonParseError.error != QJsonParseError::NoError) {
	//	return;
	//}
	QJsonObject jsonObject = jsonDocument.object();
	if (jsonObject.contains("type"))
	{
		QJsonValue JsonValue = jsonObject.value("type");
		type = JsonValue.toInt();
		if (type == 100)
		{
			bool value = JsonUtil::getInstance()->login(byteArray.data());
			QJsonObject jsonObject;
			if (value)
			{
				jsonObject.insert("result", 0);
			}
			else
			{
				jsonObject.insert("result", 1);
			}
			QJsonDocument document;
			document.setObject(jsonObject);
			QByteArray byteArray = document.toJson(QJsonDocument::Compact);
			this->write(byteArray);
		}
		else if (type == 101)
		{
			JsonUtil::getInstance()->addUser(byteArray.data());
		}
	}
}
