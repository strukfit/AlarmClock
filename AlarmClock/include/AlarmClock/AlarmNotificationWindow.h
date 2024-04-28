#pragma once

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSoundEffect>

#include "AlarmClock/AlarmNotificationWindowUI.h"
#include "AlarmClock/AlarmClockWidget.h"

class AlarmNotificationWindow : public QDialog {
	Q_OBJECT

public:
	AlarmNotificationWindow(QMainWindow* parent = nullptr, AlarmClockWidget* alarm = nullptr);
	~AlarmNotificationWindow();

signals:
	void alarmSnoozed(const int& id, const QString& name, const QTime& time);
	void resized();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	Ui::AlarmNotificationWindowClass* ui;

	AlarmClockWidget* alarm;

	QSoundEffect* alarmSound;
};