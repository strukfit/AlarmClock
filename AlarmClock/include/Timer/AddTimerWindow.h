#pragma once

#include <QTime>
#include <QApplication>

#include "TimerWindowUI.h"
#include "TimerWidget.h"

class AddTimerWindow : public QDialog
{
	Q_OBJECT

signals:
	void setTimer(const int& id, const QString& name, const QTime& time);

public:
	AddTimerWindow(QWidget* parent = nullptr);
	~AddTimerWindow();

	void setFocus();

private:
	Ui::TimerWindowClass* ui;
};