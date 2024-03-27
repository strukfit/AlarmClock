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

public:
	EditAlarmWindow(QWidget* parent = nullptr);
	~EditAlarmWindow();

	void setValues(const QString& name, const QTime& time);
	void setFocus();
	void setListId(const int& listId);

private:
	Ui::SetAlarmWindowClass* ui;

	int listId;
};