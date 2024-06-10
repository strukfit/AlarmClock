#include "Worldclock/ClockWidgetUI.h"

void ClockWidgetUI::setupUI(QWidget* ClockWidget)
{
	ClockWidget->setContentsMargins(0, 0, 0, 0);
	ClockWidget->setFixedHeight(67);
	ClockWidget->setAttribute(Qt::WA_StyledBackground, true);

	layout = new QHBoxLayout(ClockWidget);
	layout->setContentsMargins(16, 0, 16, 0);
	layout->setSpacing(38);

	dayIcon = new QSvgWidget(ClockWidget);
	dayIcon->load(QString("Resources/day-white.svg"));
	dayIcon->setFixedSize(16, 16);
	dayIcon->setStyleSheet("border: 0;");
	dayIcon->hide();

	layout->addWidget(dayIcon);

	nightIcon = new QSvgWidget(ClockWidget);
	nightIcon->load(QString("Resources/night-white.svg"));
	nightIcon->setFixedSize(16, 16);
	nightIcon->setStyleSheet("border: 0;");
	nightIcon->hide();

	layout->addWidget(nightIcon);

	time = new QLabel(ClockWidget);
	time->setStyleSheet("background-color: transparent; color: #D0D0D0; font-size: 20px; font-weight: bold; border: 0;");

	layout->addWidget(time);

	auto nameDateLayout = new QVBoxLayout(ClockWidget);
	nameDateLayout->setContentsMargins(0, 0, 0, 0);
	nameDateLayout->setSpacing(0);

	name = new QLabel(ClockWidget);
	name->setStyleSheet("background-color: transparent; color: white; font-size: 14px; font-weight: bold; border: 0;");

	date = new QLabel(ClockWidget);
	date->setStyleSheet("background-color: transparent; color: #D0D0D0; font-size: 14px; border: 0;");

	nameDateLayout->addStretch();
	nameDateLayout->addWidget(name);
	nameDateLayout->addWidget(date);
	nameDateLayout->addStretch();

	layout->addLayout(nameDateLayout);
	
	layout->addStretch();

	deleteButton = new IconPushButton(ClockWidget, "", "transparent", "transparent", "Resources/delete-grey.svg", "Resources/delete-grey.svg", "transparent", "#424242", "#363636");
	deleteButton->setFixedSize(QSize(36, 36));
	deleteButton->setIconSize(QSize(16, 16));

	deleteButton->hide();

	layout->addWidget(deleteButton);

	QMetaObject::connectSlotsByName(ClockWidget);
}