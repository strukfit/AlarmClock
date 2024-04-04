#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "IconPushButton.h"

class AlarmClockWidgetUI
{
public:
	void setupAlarmClockWidgetUI(QWidget* AlarmClockWidgetClass);

	QGridLayout* gBoxLayout;
	QLabel* time;
	QLabel* name;
	QPushButton* testButton;
	IconPushButton* deleteButton;
};

namespace Ui {
	class AlarmClockWidgetClass : public AlarmClockWidgetUI {};
} // namespace Ui