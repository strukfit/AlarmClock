#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>

#include "IconPushButton.h"
#include "ToggleSwitch.h"

class AlarmClockWidgetUI
{
public:
	void setupUI(QWidget* AlarmClockWidgetClass);

	QGridLayout* gBoxLayout;
	QLabel* time;
	QHBoxLayout* ramainingTimeLayout;
	QSvgWidget* alarmIcon;
	QLabel* remainingTime;
	QLabel* name;
	ToggleSwitch* toggleSwitch;
	IconPushButton* deleteButton;
};

namespace Ui {
	class AlarmClockWidgetClass : public AlarmClockWidgetUI {};
} // namespace Ui