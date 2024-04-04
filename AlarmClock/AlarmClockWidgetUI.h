#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

class AlarmClockWidgetUI
{
public:
	void setupAlarmClockWidgetUI(QWidget* AlarmClockWidgetClass);

	QGridLayout* gBoxLayout;
	QLabel* time;
	QLabel* name;
	QPushButton* testButton;
};

namespace Ui {
	class AlarmClockWidgetClass : public AlarmClockWidgetUI {};
} // namespace Ui