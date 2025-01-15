#pragma once

#include <QtSql>
#include <QObject>

class DataBase : public QObject
{
	Q_OBJECT
	public : explicit DataBase(QObject *parent = nullptr);

	QSqlQuery query;
	
	int read_db();
	void add_abonent(QString *ab);
	static bool create_connection();

};