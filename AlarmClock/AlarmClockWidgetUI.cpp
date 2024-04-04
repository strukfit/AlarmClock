#include "AlarmClockWidgetUI.h"

void AlarmClockWidgetUI::setupAlarmClockWidgetUI(QWidget* AlarmClockWidgetClass)
{
	gBoxLayout = new QGridLayout(AlarmClockWidgetClass);
	gBoxLayout->setContentsMargins(0, 0, 0, 0);

	time = new QLabel(AlarmClockWidgetClass);
	time->setStyleSheet("background-color: transparent; color: white; font-size: 50px; font-weight: bold;");

	name = new QLabel(AlarmClockWidgetClass);
	name->setStyleSheet("background-color: transparent; color: white; font-size: 20px;");

	testButton = new QPushButton("test", AlarmClockWidgetClass);

	deleteButton = new IconPushButton(AlarmClockWidgetClass, "", "transparent", "transparent", "Resources/delete-grey.svg", "Resources/delete-grey.svg", "transparent", "#424242", "#363636");
	deleteButton->setFixedSize(QSize(36, 36));
	deleteButton->setIconSize(QSize(16, 16));

	gBoxLayout->addWidget(time, 0, 0);
	gBoxLayout->addWidget(name, 1, 0);
	gBoxLayout->addWidget(testButton, 0, 1);
	gBoxLayout->addWidget(deleteButton, 0, 1);
	deleteButton->hide();

	AlarmClockWidgetClass->setLayout(gBoxLayout);

	QMetaObject::connectSlotsByName(AlarmClockWidgetClass);
}