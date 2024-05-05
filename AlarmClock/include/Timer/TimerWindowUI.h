#pragma once

#include <QLabel>
#include <QBoxLayout>
#include <QSvgWidget>
#include <QtSvg/QSvgRenderer>
#include <QSettings>
#include <QApplication>
#include <QTime>

#include "AlarmClock/AlarmWindowUI.h"
#include "AlarmClock/TimeSpinBox.h"
#include "AlarmClock/TimeWrapperWidget.h"
#include "AlarmClock/ArrowPushButton.h"
#include "AlarmClock/NameLineEdit.h"
#include "IconPushButton.h"

class TimerWindowUI
{
public:
	void setupAddTimerWindowUI(QDialog* TimerWindowClass);
	void setupEditTimerWindowUI(QDialog* TimerWindowClass);
	void setValues(const QString& name, const QTime& time);

	QLabel* title;
	QVBoxLayout* setTimerWindowVLayout;
	QHBoxLayout* timeSelectorHBoxLayout;
	TimeWrapperWidget* timeWrapperWidget;
	TimeWrapperChildWidget* timeSelectorWidget;
	TimeSpinBox* hoursSpinBox;
	TimeSpinBox* minutesSpinBox;
	TimeSpinBox* secondsSpinBox;
	QHBoxLayout* editNameHBoxLayout;
	QSvgWidget* editSvgWidget;
	NameLineEdit* nameLineEdit;
	ArrowPushButton* arrowUpButton1;
	ArrowPushButton* arrowUpButton2;
	ArrowPushButton* arrowUpButton3;
	ArrowPushButton* arrowDownButton1;
	ArrowPushButton* arrowDownButton2;
	ArrowPushButton* arrowDownButton3;
	TimeWrapperWidget* editNameWrapperWidget;
	TimeWrapperChildWidget* editNameWidget;
	QHBoxLayout* nameLineEditLayout;
	IconPushButton* xButton;
	IconPushButton* setTimerButton;
	IconPushButton* cancelButton;
	QHBoxLayout* saveCancelLayout;

	IconPushButton* deleteButton;

private:
	const QString activeAccentColor = "#78bcec";
	const QString inactiveAccentColor = "#9c9c9c";

	QString defaultName = "Timer";
};

namespace Ui {
	class SetTimerWindowClass : public TimerWindowUI {};
} // namespace Ui