#pragma once

#include <QObject>

class JsonUtil : public QObject
{
	Q_OBJECT

public:
	JsonUtil(QObject *parent = Q_NULLPTR);
	~JsonUtil();

	static JsonUtil * getInstance();

	bool login(const char * data);

	bool addUser(const char * data);
};
