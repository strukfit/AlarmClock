#pragma once
#include "UI.h"
#include <QTime>

class SetAlarmWindow : public QDialog
{
	Q_OBJECT

signals:
	void setAlarm(const QTime& time, const QString name);

public:
	SetAlarmWindow(QWidget* parent = nullptr);
	~SetAlarmWindow();

private:
	Ui::SetAlarmWindowClass* ui;
};