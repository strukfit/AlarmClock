#pragma once

#include <QTime>
#include <QApplication>

#include "SetAlarmWindowUI.h"
#include "AlarmClockWidget.h"

class SetAlarmWindow : public QDialog
{
	Q_OBJECT

signals:
	void setAlarm(const int& id, const QString& name, const QTime& time);

public:
	SetAlarmWindow(QWidget* parent = nullptr);
	~SetAlarmWindow();

	void setDefaultValues();
	void setDefaultFocus();

private:
	Ui::SetAlarmWindowClass* ui;
};