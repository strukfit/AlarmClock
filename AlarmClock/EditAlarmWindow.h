#pragma once

#include <QTime>
#include <QApplication>

#include "AlarmWindowUI.h"
#include "AlarmClockWidget.h"

class EditAlarmWindow : public QDialog
{
	Q_OBJECT

//signals:
//	void setAlarm(const int& id, const QString& name, const QTime& time);

public:
	EditAlarmWindow(QWidget* parent = nullptr);
	~EditAlarmWindow();

	void setValues(const QString& name, const QTime& time);
	void setFocus();

private:
	Ui::SetAlarmWindowClass* ui;
};