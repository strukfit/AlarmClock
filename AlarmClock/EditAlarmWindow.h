#pragma once

#include <QTime>
#include <QApplication>

#include "AlarmWindowUI.h"
#include "AlarmClockWidget.h"

class EditAlarmWindow : public QDialog
{
	Q_OBJECT

signals:
	void updateAlarm(AlarmClockWidget* alarm, const QString& name, const QTime& time);
	void deleteAlarm(AlarmClockWidget* alarm);

public:
	EditAlarmWindow(QWidget* parent = nullptr, AlarmClockWidget* alarm = nullptr);
	~EditAlarmWindow();

	void setFocus();

private:
	Ui::SetAlarmWindowClass* ui = new Ui::SetAlarmWindowClass;

	AlarmClockWidget* alarm;
};