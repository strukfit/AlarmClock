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

	void selectAllAlarms();
	void selectAllTimers();

	int getLastAlarmId();
	int getLastTimerId();

public slots:
	void insertAlarmData(const int& id, const QString& name, const QTime& time);
	void updateAlarmData(const int& id, const QString& name, const QTime& time);
	void deleteAlarmData(const int& id);
	
	void insertTimerData(const int& id, const QString& name, const QTime& time);
	void updateTimerData(const int& id, const QString& name, const QTime& time);
	void deleteTimerData(const int& id);

signals:
	void alarmDataReceived(const int& id, const QString& name, const QTime& time);
	void timerDataReceived(const int& id, const QString& name, const QTime& time);

private:
	QSqlDatabase db;
};