#pragma once

#include <QTime>
#include <QApplication>

#include "TimerWindowUI.h"
#include "TimerWidget.h"

class EditTimerWindow : public QDialog
{
	Q_OBJECT

signals:
	void updateTimer(TimerWidget* timer, const QString& name, const QTime& time);
	void deleteTimer(TimerWidget* timer);

public:
	EditTimerWindow(QWidget* parent = nullptr, TimerWidget* timer = nullptr);
	~EditTimerWindow();

	void setFocus();

private:
	Ui::TimerWindowClass* ui;

	TimerWidget* timer;
};