#pragma once

#if defined(_WIN64)
#include <QSqlDatabase>
#elif defined(__linux__)
#include <QtSql/QSqlDatabase>
#endif

#include <string>
#include <vector>
#include <memory>

#include <QVector>
#include <QString>

class DataBase
{
private:
    QSqlDatabase _mysql;
	bool _connection;
	void close();

public:
	DataBase();
	~DataBase();
    bool connect(QString host, unsigned int port, QString dbname, QString user, QString password);
	bool hasConnection();
    QVector<QString> queryResult(QString queryText);
    void executeQueryWithoutResult(QString queryText);
};

