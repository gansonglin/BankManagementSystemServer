#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>

#include "databaseutil.h"
#include <time.h>

DatabaseUtil::DatabaseUtil(QObject *parent)
	: QObject(parent)
{
	init();
}

DatabaseUtil::~DatabaseUtil()
{
}

DatabaseUtil * DatabaseUtil::getInstance()
{
	static DatabaseUtil instance(nullptr);
	return &instance;
}

void DatabaseUtil::init()
{
	m_database = QSqlDatabase::addDatabase("QMYSQL");
	m_database.setHostName("127.0.0.1");
	m_database.setDatabaseName("bankmanagementsystem");
	m_database.setPort(3306);
	m_database.setUserName("root");
	bool ret = m_database.open();
	if (!ret)
	{
		qDebug() << "open is failure..." <<" "<< m_database.lastError();
	}
}

QString DatabaseUtil::getBankCardByUsername(const QString & username)
{
	char sql[200] = "";
	snprintf(sql, sizeof(sql), "select BCno from User,BankCard where User.Uname=BankCard.Uname and User.Uname='%s';", username.toLocal8Bit().data());

	QSqlQuery sqlQuery = m_database.exec(sql);
	while (sqlQuery.next())
	{
		return sqlQuery.value(0).toString();
	}
}

bool DatabaseUtil::addUser(const QString & userName, const QString & passWord, const QString & name, const QString & id, const QString & sex, const QString & phone, const QString & mail, const QString & address, const QString & weight, const QString & height,QString & bankCard)
{
	char sql[300] = "";
	int result;
	char bc_no[17] = "";

	sprintf(sql, "select * from user_table where userName = '%s';", userName.toLocal8Bit().data());
	QSqlQuery sqlQuery = m_database.exec(sql);

	//QSqlQuery sqlQuery;
	//sqlQuery.prepare(sql);
	//sqlQuery.exec();
	
	while (sqlQuery.next())
	{
		if (sqlQuery.isValid())
		{
			return false; //用户已经存在
		}
	}

	snprintf(bc_no, sizeof(bc_no), "%16ld", time(NULL));
	for (int i = 0; i < 16; ++i)
	{
		if (bc_no[i] == ' ')
			bc_no[i] = '0';
	}
	bankCard = QString::fromLocal8Bit(bc_no);
	sprintf(sql, "insert into user_table(userName,passWord,name,id,sex,phone,mail,address,weight,height)values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');", userName.toLocal8Bit().data(), passWord.toLocal8Bit().data(), name.toLocal8Bit().data(), id.toLocal8Bit().data(), sex.toLocal8Bit().data(), phone.toLocal8Bit().data(), mail.toLocal8Bit().data(), address.toLocal8Bit().data(), weight.toLocal8Bit().data(), height.toLocal8Bit().data());

	sqlQuery =  m_database.exec(sql);

	//qDebug() << sqlQuery.lastError();
	
	//查询当前用户的userId
	
	sprintf(sql, "select userId from user_table where userName='%s'", userName.toLocal8Bit().data());
	sqlQuery = m_database.exec(sql);
	QString userId ;
	while (sqlQuery.next())
	{
		userId = sqlQuery.value(0).toString();
	}
	QDateTime dataTime = QDateTime::currentDateTime();
	//QString time = dataTime.toString("yyyy-MM-dd-hh:mm:ss");
	memset(sql, 0, sizeof(sql));
	snprintf(sql, sizeof(sql), "insert into bank_card_table (num, money, date,userId)"\
		" values ('%s','%s',%s,'%s');",
		bankCard.toLocal8Bit().data(), "0", "CURRENT_TIME()", userId.toLocal8Bit().data());
	sqlQuery = m_database.exec(sql);

	//插入记录 
	snprintf(sql, sizeof(sql), "insert into transacation_table (num, type, money,date,userId)"\
		" values ('%s','%s','%s',%s,'%s');",
		bankCard.toLocal8Bit().data(), "open", "0","CURRENT_TIME()", userId.toLocal8Bit().data());
	sqlQuery = m_database.exec(sql);

	return true;
}

bool DatabaseUtil::deleteUser(const QString & username, const QString & password)
{
	char sql[300] = "";
	int result;

	snprintf(sql, sizeof(sql), "delete from User"\
		" where Uname = '%s' and Upwd = '%s' and Utype = '%s'",
		username.data(), password.data(), "user");

	m_database.transaction();

	QSqlQuery sqlQuery = m_database.exec(sql);
	if (!sqlQuery.isValid())
	{
		m_database.rollback();
	}
	else
	{
		m_database.commit();
	}
	return true;
}

bool DatabaseUtil::login(const QString & username, const QString & password, const QString & userType)
{
	char sql[200] = "";

	sprintf(sql, "select * from user_table where userName = '%s'and passWord='%s';", username.toLocal8Bit().data(), password.toLocal8Bit().data());

	QSqlQuery sqlQuery = m_database.exec(sql);
	while (sqlQuery.next())
	{
		//sqlQuery.value(0).toString();
		return true;
	}
	return false;
}

bool DatabaseUtil::addMoney(const QString & username,int money, ActionType actionType)
{
	QString bankCard = getBankCardByUsername(username);
	updateBankMoney(bankCard, money, actionType);
	return false;
}

bool DatabaseUtil::updateBankMoney(const QString &bankCard, int addMoney, ActionType actionType)
{
	char sql[200] = "";
	snprintf(sql, sizeof(sql), "select BCmon from BankCard where BCno='%s';", bankCard.toLocal8Bit().data());
	
	QSqlQuery sqlQuery = m_database.exec(sql);
	QString bankMoney = "";
	while (sqlQuery.next())
	{
		bankMoney = sqlQuery.value(0).toString();
	}

	double oldMoney = bankMoney.toDouble();//得到原来银行卡中的钱
	printf("old_mon = %lf\n", oldMoney);
	if ((addMoney < 0) && (oldMoney < abs(addMoney))) {  //取的钱不能超过卡里的钱
		printf("No enough money\n");
		return false;
	}

	oldMoney += addMoney;
	memset(sql, 0, sizeof(sql));
	snprintf(sql, sizeof(sql), "update BankCard set BCmon=%f where BCno='%s';", oldMoney, bankCard.toLocal8Bit().data());
	m_database.exec(sql);
		
	char *type2 = NULL;

	switch (actionType)
	{
	case DatabaseUtil::save:
		type2 = "save";
		break;
	case DatabaseUtil::take:
		type2 = "take";
		break;
	case DatabaseUtil::turnOut:
		type2 = "turnOut";
		break;
	case DatabaseUtil::turnIn:
		type2 = "turnIn";
		break;
	default:
		break;
	}

	sprintf(sql, "insert into BankCardDetail values('%s', '%s', '%d', datetime('now'));", bankCard.toLocal8Bit().data(), type2, abs(addMoney));
	m_database.exec(sql);
	return true;	
}

bool DatabaseUtil::trunMoney(const QString & username, const QString destBankCard, double money)
{
	QString bankCard = getBankCardByUsername(username);
	updateBankMoney(bankCard, -money, DatabaseUtil::turnOut);
	updateBankMoney(destBankCard, money, DatabaseUtil::turnIn);

	char sql[1024] = { 0 };
	sprintf(sql, "insert into TransferAccount values('%s', '%s', '%lf', datetime('now'));", bankCard.toLocal8Bit().data(), destBankCard.toLocal8Bit().data(), money);
	m_database.exec(sql);
	return true;
}

bool DatabaseUtil::getDetail(const QString & username, QList <QList <QString>> &list)
{
	QString bankCard = getBankCardByUsername(username);
	char sql[1024] = "";
	snprintf(sql, sizeof(sql), "select * from BankCardDetail where BCno='%s';", bankCard.toLocal8Bit().data());
	QSqlQuery sqlQuery = m_database.exec(sql);
	while (sqlQuery.next())
	{
		QList <QString> strList;
		for (int index = 0; index < 4 ; index++)
		{
			strList.append(sqlQuery.value(index).toString());
		}
		list.append(strList);
	}
	return true;
}

