#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTime>

class DatabaseManager : public QObject
{
	Q_OBJECT

public:
	DatabaseManager(QObject* parent);

	bool open();

	void close();

	bool tableInit();

	void selectAll();

public slots:
	void insertData(const int& id, const QString& name, const QTime& time);

signals:
	void dataReceived(const int& id, const QString& name, const QTime& time);

private:
	QSqlDatabase db;
};