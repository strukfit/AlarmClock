#pragma once

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSoundEffect>

#include "Timer/TimerNotificationWindowUI.h"
#include "Timer/TimerWidget.h"

class TimerNotificationWindow : public QDialog {
	Q_OBJECT

public:
	TimerNotificationWindow(QMainWindow* parent = nullptr, TimerWidget* timer = nullptr);
	~TimerNotificationWindow();

signals:
	void alarmSnoozed(const int& id, const QString& name, const QTime& time);
	void resized();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	Ui::TimerNotificationWindowClass* ui;

	TimerWidget* timer;

	QSoundEffect* alarmSound;
};