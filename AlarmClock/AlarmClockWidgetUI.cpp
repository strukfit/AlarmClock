#include "AlarmClockWidgetUI.h"

void AlarmClockWidgetUI::setupAlarmClockWidgetUI(QWidget* AlarmClockWidget)
{
	AlarmClockWidget->setContentsMargins(0, 0, 0, 0);
	//AlarmClockWidget->setMinimumSize(QSize(0, 180));
	AlarmClockWidget->setFixedHeight(180);
	AlarmClockWidget->setAttribute(Qt::WA_StyledBackground, true);
	AlarmClockWidget->setStyleSheet("background-color: #323232; border-radius: 10px;");

	gBoxLayout = new QGridLayout(AlarmClockWidget);
	gBoxLayout->setContentsMargins(0, 0, 0, 0);

	time = new QLabel(AlarmClockWidget);
	time->setStyleSheet("background-color: transparent; color: white; font-size: 50px; font-weight: bold;");

	name = new QLabel(AlarmClockWidget);
	name->setStyleSheet("background-color: transparent; color: white; font-size: 20px;");

	testButton = new QPushButton("test", AlarmClockWidget);

	deleteButton = new IconPushButton(AlarmClockWidget, "", "transparent", "transparent", "Resources/delete-grey.svg", "Resources/delete-grey.svg", "transparent", "#424242", "#363636");
	deleteButton->setFixedSize(QSize(36, 36));
	deleteButton->setIconSize(QSize(16, 16));

	gBoxLayout->addWidget(time, 0, 0);
	gBoxLayout->addWidget(name, 1, 0);
	gBoxLayout->addWidget(testButton, 0, 1);
	gBoxLayout->addWidget(deleteButton, 0, 1);
	deleteButton->hide();

	QMetaObject::connectSlotsByName(AlarmClockWidget);
}