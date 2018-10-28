#pragma once

#include <QObject>
#include <QSqlDatabase>

class DatabaseUtil : public QObject
{
	Q_OBJECT

public:
	enum ActionType //交易类型
	{
		save, //存款
		take, //取款
		turnOut, //转出
		turnIn //转入
	};

	DatabaseUtil(QObject *parent);
	~DatabaseUtil();

	static DatabaseUtil * getInstance();

private:
	void init();

	QString getBankCardByUsername(const QString & username);
private:
	QSqlDatabase m_database;

public:
	bool addUser(const QString & userName, const QString & passWord, const QString & name, const QString & id, const QString & sex, const QString & phone, const QString & mail, const QString & address, const QString & weight, const QString & height, QString & bankCard);
	bool deleteUser(const QString & username, const QString & password);
	bool login(const QString & username,const QString & password,const QString & userType);
	bool addMoney(const QString & username, int money, ActionType actionType);
	bool updateBankMoney(const QString &bankCard, int addMoney, ActionType actionType);
	bool trunMoney(const QString & username, const QString destBankCard, double money);
	bool getDetail(const QString & username,QList <QList <QString>> &list);
};
