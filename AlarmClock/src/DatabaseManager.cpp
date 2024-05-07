#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(QObject* parent) :
	QObject(parent)
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("database.db");
}

bool DatabaseManager::open()
{
	if (!db.open())
	{
		QMessageBox::critical(nullptr, "Fatal error", "Error: Failed to connect to database: " + db.lastError().text());
		return false;
	}
	//qDebug() << "Connected to database.";
	return true;
}

void DatabaseManager::close()
{
	db.close();
}

bool DatabaseManager::tableInit()
{
	QSqlQuery query;

	if (!query.exec("CREATE TABLE IF NOT EXISTS AlarmClocks (id INTEGER PRIMARY KEY, name TEXT, time TEXT)"))
	{
		QMessageBox::critical(nullptr, "Fatal error", "Error: Failed to create table: " + query.lastError().text());
		return false;
	}

	if (!query.exec("CREATE TABLE IF NOT EXISTS Timers (id INTEGER PRIMARY KEY, name TEXT, time TEXT)"))
	{
		QMessageBox::critical(nullptr, "Fatal error", "Error: Failed to create table: " + query.lastError().text());
		return false;
	}

	return true;
}

void DatabaseManager::selectAllAlarms()
{
	QSqlQuery query("SELECT * FROM AlarmClocks");
	while (query.next())
	{
		int id = query.value("id").toInt();
		QString name = query.value("name").toString();
		QTime time(QTime::fromString(query.value("time").toString(), ("hh:mm")));

		emit alarmDataReceived(id, name, time);
	}
}

void DatabaseManager::selectAllTimers()
{
	QSqlQuery query("SELECT * FROM Timers");
	while (query.next())
	{
		int id = query.value("id").toInt();
		QString name = query.value("name").toString();
		QTime time(QTime::fromString(query.value("time").toString(), ("hh:mm:ss")));

		emit timerDataReceived(id, name, time);
	}
}

int DatabaseManager::getLastAlarmId()
{
	QSqlQuery query("SELECT * FROM AlarmClocks ORDER BY id DESC LIMIT 1;");
	query.next();
	return query.value("id").toInt();
}

int DatabaseManager::getLastTimerId()
{
	QSqlQuery query("SELECT * FROM Timers ORDER BY id DESC LIMIT 1;");
	query.next();
	return query.value("id").toInt();
}

void DatabaseManager::insertAlarmData(const int& id, const QString& name, const QTime& time)
{
	QSqlQuery query;
	query.prepare("INSERT INTO AlarmClocks (id, name, time) VALUES (:id, :name, :time);");
	query.bindValue(":id", id);
	query.bindValue(":name", name);
	query.bindValue(":time", time.toString("hh:mm"));
	query.exec();
}

void DatabaseManager::updateAlarmData(const int& id, const QString& name, const QTime& time)
{
	QSqlQuery query;
	query.prepare("UPDATE AlarmClocks SET name = :name, time = :time WHERE id = :id;");
	query.bindValue(":id", id);
	query.bindValue(":name", name);
	query.bindValue(":time", time.toString("hh:mm"));
	query.exec();
}

void DatabaseManager::deleteAlarmData(const int& id)
{
	QSqlQuery query;
	query.prepare("DELETE FROM AlarmClocks WHERE id = :id;");
	query.bindValue(":id", id);
	query.exec();
}

void DatabaseManager::insertTimerData(const int& id, const QString& name, const QTime& time)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Timers (id, name, time) VALUES (:id, :name, :time);");
	query.bindValue(":id", id);
	query.bindValue(":name", name);
	query.bindValue(":time", time.toString("hh:mm:ss"));
	query.exec();
}

void DatabaseManager::updateTimerData(const int& id, const QString& name, const QTime& time)
{
	QSqlQuery query;
	query.prepare("UPDATE Timers SET name = :name, time = :time WHERE id = :id;");
	query.bindValue(":id", id);
	query.bindValue(":name", name);
	query.bindValue(":time", time.toString("hh:mm:ss"));
	query.exec();
}

void DatabaseManager::deleteTimerData(const int& id)
{
	QSqlQuery query;
	query.prepare("DELETE FROM Timers WHERE id = :id;");
	query.bindValue(":id", id);
	query.exec();
}
