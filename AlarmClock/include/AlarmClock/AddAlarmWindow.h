#pragma once

#include <QTime>
#include <QApplication>

#include "AlarmWindowUI.h"
#include "AlarmClockWidget.h"

class AddAlarmWindow : public QDialog
{
	Q_OBJECT

signals:
	void setAlarm(const int& id, const QString& name, const QTime& time);

public:
	AddAlarmWindow(QWidget* parent = nullptr);
	~AddAlarmWindow();

	void setDefaultValues();
	void setFocus();

private:
	Ui::SetAlarmWindowClass* ui;
};