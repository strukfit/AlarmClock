#pragma once

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "AlarmClock/AlarmNotificationWindowUI.h"
#include "AlarmClock/AlarmClockWidget.h"

class AlarmNotificationWindow : public QDialog{
	Q_OBJECT

public:
	AlarmNotificationWindow(QMainWindow* parent = nullptr, AlarmClockWidget* alarm = nullptr);
	~AlarmNotificationWindow();

	Q_SIGNAL void alarmSnoozed(const int& id, const QString& name, const QTime& time);

private:
	Ui::AlarmNotificationWindowClass* ui;

	AlarmClockWidget* alarm;

	/*std::map<QString, int> snoozeMap = {
		{"5 minutes", 300},
		{"10 minutes", 600},
		{"20 minutes", 1200},
		{"30 minutes", 1800},
		{"1 hour", 3600}
	};*/
};