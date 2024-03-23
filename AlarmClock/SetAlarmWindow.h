#pragma once
#include "SetAlarmWindowUI.h"
#include <QTime>
#include <QApplication>

class SetAlarmWindow : public QDialog
{
	Q_OBJECT

signals:
	void setAlarm(const QTime& time, const QString name);

public:
	SetAlarmWindow(QWidget* parent = nullptr);
	~SetAlarmWindow();

	void setDefaultValues();
	void setDefaultFocus();

private:
	Ui::SetAlarmWindowClass* ui;
};