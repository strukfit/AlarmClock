#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "IconPushButton.h"
#include "ToggleSwitch.h"

class AlarmClockWidgetUI
{
public:
	void setupAlarmClockWidgetUI(QWidget* AlarmClockWidgetClass);

	QWidget* centralWidget;
	QGridLayout* gBoxLayout;
	QLabel* time;
	QLabel* name;
	ToggleSwitch* toggleSwitch;
	IconPushButton* deleteButton;
};

namespace Ui {
	class AlarmClockWidgetClass : public AlarmClockWidgetUI {};
} // namespace Ui