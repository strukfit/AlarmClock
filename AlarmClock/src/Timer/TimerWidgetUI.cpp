#include "Timer/TimerWidgetUI.h"

void TimerWidgetUI::setupUI(QWidget* TimerWidget)
{
	TimerWidget->setContentsMargins(0, 0, 0, 0);
	TimerWidget->setFixedHeight(324);
	TimerWidget->setAttribute(Qt::WA_StyledBackground, true);

	gBoxLayout = new QGridLayout(TimerWidget);
	gBoxLayout->setContentsMargins(16, 8, 20, 32);
	
	time = new QLabel(TimerWidget);
	time->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 60px; font-weight: bold; border: 0;");

	name = new QLabel(TimerWidget);
	name->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 20px; font-weight: bold; border: 0;");

	deleteButton = new IconPushButton(TimerWidget, "", "transparent", "transparent", "Resources/delete-grey.svg", "Resources/delete-grey.svg", "transparent", "#424242", "#363636");
	deleteButton->setFixedSize(QSize(36, 36));
	deleteButton->setIconSize(QSize(16, 16));

	gBoxLayout->addWidget(name, 0, 0);
	gBoxLayout->addWidget(time, 1, 1);
	gBoxLayout->addWidget(deleteButton, 0, 2);
	deleteButton->hide();

	QMetaObject::connectSlotsByName(TimerWidget);
}