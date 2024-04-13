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
	//qDebug() << "Disconnected from database.";
}

bool DatabaseManager::tableInit()
{
	QSqlQuery query;
	if (!query.exec("CREATE TABLE IF NOT EXISTS AlarmClocks (id INTEGER PRIMARY KEY, name TEXT, time TEXT)"))
	{
		QMessageBox::critical(nullptr, "Fatal error", "Error: Failed to create table: " + query.lastError().text());
		return false;
	}
	return true;
}

void DatabaseManager::selectAll()
{
	QSqlQuery query("SELECT * FROM AlarmClocks");
	while (query.next())
	{
		int id = query.value("id").toInt();
		QString name = query.value("name").toString();
		QTime time(QTime::fromString(query.value("time").toString(), ("hh:mm")));

		emit dataReceived(id, name, time);
	}
}

int DatabaseManager::getLastId()
{
	QSqlQuery query("SELECT * FROM AlarmClocks ORDER BY id DESC LIMIT 1;");
	query.next();
	return query.value("id").toInt();
}

void DatabaseManager::insertData(const int& id, const QString& name, const QTime& time)
{
	QSqlQuery query;
	query.prepare("INSERT INTO AlarmClocks (id, name, time) VALUES (:id, :name, :time);");
	query.bindValue(":id", id);
	query.bindValue(":name", name);
	query.bindValue(":time", time.toString("hh:mm"));
	query.exec();
}

void DatabaseManager::updateData(const int& id, const QString& name, const QTime& time)
{
	QSqlQuery query;
	query.prepare("UPDATE AlarmClocks SET name = :name, time = :time WHERE id = :id;");
	query.bindValue(":id", id);
	query.bindValue(":name", name);
	query.bindValue(":time", time.toString("hh:mm"));
	query.exec();
}

void DatabaseManager::deleteData(const int& id)
{
	QSqlQuery query;
	query.prepare("DELETE FROM AlarmClocks WHERE id = :id;");
	query.bindValue(":id", id);
	query.exec();
}
