#include "AlarmClock/AlarmClockWidgetUI.h"

void AlarmClockWidgetUI::setupUI(QWidget* AlarmClockWidget)
{
	AlarmClockWidget->setContentsMargins(0, 0, 0, 0);
	AlarmClockWidget->setFixedHeight(150);
	AlarmClockWidget->setAttribute(Qt::WA_StyledBackground, true);

	gBoxLayout = new QGridLayout(AlarmClockWidget);
	gBoxLayout->setContentsMargins(16, 8, 20, 32);

	time = new QLabel(AlarmClockWidget);
	time->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 60px; font-weight: bold; border: 0;");

	ramainingTimeLayout = new QHBoxLayout(AlarmClockWidget);
	ramainingTimeLayout->setSpacing(10);
	ramainingTimeLayout->setContentsMargins(0, 0, 0, 0);

	alarmIcon = new QSvgWidget(AlarmClockWidget);
	alarmIcon->load(QString("Resources/alarm-grey.svg"));
	alarmIcon->setFixedSize(16, 17);
	alarmIcon->setStyleSheet("border: 0;");

	remainingTime = new QLabel(AlarmClockWidget);
	remainingTime->setStyleSheet("background-color: transparent; color: #C3C3C3; font-size: 12px; border: 0;");

	ramainingTimeLayout->addWidget(alarmIcon);
	ramainingTimeLayout->addWidget(remainingTime);

	name = new QLabel(AlarmClockWidget);
	name->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 20px; font-weight: bold; border: 0;");

	toggleSwitch = new ToggleSwitch(AlarmClockWidget, "#76B9ED");

	deleteButton = new IconPushButton(AlarmClockWidget, "", "transparent", "transparent", "Resources/delete-grey.svg", "Resources/delete-grey.svg", "transparent", "#424242", "#363636");
	deleteButton->setFixedSize(QSize(36, 36));
	deleteButton->setIconSize(QSize(16, 16));

	gBoxLayout->addWidget(time, 0, 0);
	gBoxLayout->addLayout(ramainingTimeLayout, 1, 0);
	gBoxLayout->addWidget(name, 2, 0);
	gBoxLayout->addWidget(toggleSwitch, 0, 1);
	gBoxLayout->addWidget(deleteButton, 0, 1);
	deleteButton->hide();

	QMetaObject::connectSlotsByName(AlarmClockWidget);
}