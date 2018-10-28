#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

#include "jsonutil.h"
#include "databaseutil.h"

JsonUtil::JsonUtil(QObject *parent)
	: QObject(parent)
{
}

JsonUtil::~JsonUtil()
{
}

JsonUtil * JsonUtil::getInstance()
{
	static JsonUtil instance;
	return &instance;
}

bool JsonUtil::login(const char * data)
{
	QString username;
	QString password;
	QJsonParseError jsonParseError = QJsonParseError();
	QJsonDocument jsonDocument = QJsonDocument::fromJson((QByteArray(data)), &jsonParseError);
	if (jsonParseError.error != QJsonParseError::NoError) {
		return false;
	}
	QJsonObject jsonObject = jsonDocument.object();
	if (jsonObject.contains("username"))
	{
		QJsonValue jsonValue = jsonObject.value("username");
		if (jsonValue.isString())
		{
			username = jsonValue.toString();
		}
	}
	if (jsonObject.contains("password"))
	{
		QJsonValue jsonValue = jsonObject.value("password");
		if (jsonValue.isString())
		{
			password = jsonValue.toString();
		}
	}
	bool ret = DatabaseUtil::getInstance()->login(username, password, "");
	return ret;
}

bool JsonUtil::addUser(const char * data)
{
	QString username;
	QString password;
	QJsonParseError jsonParseError = QJsonParseError();
	QJsonDocument jsonDocument = QJsonDocument::fromJson((QByteArray(data)), &jsonParseError);
	if (jsonParseError.error != QJsonParseError::NoError) {
		return false;
	}
	QJsonObject jsonObject = jsonDocument.object();
	if (jsonObject.contains("username"))
	{
		QJsonValue jsonValue = jsonObject.value("username");
		if (jsonValue.isString())
		{
			username = jsonValue.toString();
		}
	}
	if (jsonObject.contains("password"))
	{
		QJsonValue jsonValue = jsonObject.value("password");
		if (jsonValue.isString())
		{
			password = jsonValue.toString();
		}
	}
	//DatabaseUtil::getInstance()->addUser(username, password, "");
	return false;
}
