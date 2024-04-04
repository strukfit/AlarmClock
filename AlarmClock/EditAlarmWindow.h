#pragma once

#include <QTime>
#include <QApplication>

#include "AlarmWindowUI.h"
#include "AlarmClockWidget.h"

class EditAlarmWindow : public QDialog
{
	Q_OBJECT

signals:
	void updateAlarm(const int& listId, const QString& name, const QTime& time);
	void deleteAlarm(const int& listId);

public:
	EditAlarmWindow(QWidget* parent = nullptr, const int& listId = NULL, const QString& name = NULL, const QTime& time = QTime());
	~EditAlarmWindow();

	void setFocus();

private:
	Ui::SetAlarmWindowClass* ui = new Ui::SetAlarmWindowClass;

	int listId;
};