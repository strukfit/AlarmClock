#include "UI.h"

void UI::setupMainWindowUI(QMainWindow* MainWindowClass)
{
	mainWindowCentralWidget = new QWidget(MainWindowClass);

	vBoxLayout = new QVBoxLayout(mainWindowCentralWidget);
	
	alarmsListWidget = new QListWidget(mainWindowCentralWidget);

	alarmsListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	alarmsListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	alarmsListWidget->setStyleSheet("QListWidget::item { background-color: #323232; border-radius: 5px; margin-left: 10px; margin-right: 10px; margin-bottom: 5px; margin-top: 5px; }");

	mainWindowSetAlarmButton = new QPushButton("openSetAlarmWindowButton", mainWindowCentralWidget);
	mainWindowSetAlarmButton->setObjectName("mainWindowSetAlarmButton");

	vBoxLayout->addWidget(alarmsListWidget);
	vBoxLayout->addWidget(mainWindowSetAlarmButton);

	MainWindowClass->setLayout(vBoxLayout);

	MainWindowClass->setCentralWidget(mainWindowCentralWidget);

	QMetaObject::connectSlotsByName(MainWindowClass);

}

void UI::setupSetAlarmWindowUI(QDialog* SetAlarmWindowClass)
{
	setAlarmWindowVLayout = new QVBoxLayout(SetAlarmWindowClass);

	timeSelectorHBoxLayout = new QHBoxLayout(SetAlarmWindowClass);

	TimeSpinBox* hourSpinBox = new TimeSpinBox(SetAlarmWindowClass, 0, 23);
	TimeSpinBox* minutesSpinBox = new TimeSpinBox(SetAlarmWindowClass, 0, 59);

	timeSelectorHBoxLayout->addWidget(hourSpinBox);

	separatorLabel = new QLabel(":");
	separatorLabel->setStyleSheet(" font-size: 20px ");

	timeSelectorHBoxLayout->addWidget(separatorLabel);
	timeSelectorHBoxLayout->addWidget(minutesSpinBox);

	setAlarmWindowSetAlarmButton = new QPushButton("setAlarmButton", SetAlarmWindowClass);
	setAlarmWindowSetAlarmButton->setObjectName("setAlarmWindowSetAlarmButton");

	setAlarmWindowVLayout->addLayout(timeSelectorHBoxLayout);
	setAlarmWindowVLayout->addWidget(setAlarmWindowSetAlarmButton);

	SetAlarmWindowClass->setLayout(setAlarmWindowVLayout);

	QMetaObject::connectSlotsByName(SetAlarmWindowClass);
}

void UI::setupAlarmClockWidgetUI(QWidget* AlarmClockWidgetClass)
{
	gBoxLayout = new QGridLayout(AlarmClockWidgetClass);

	time = new QLabel(AlarmClockWidgetClass);
	time->setStyleSheet("color: white; font-size: 50px; font-weight: bold;");

	name = new QLabel(AlarmClockWidgetClass);
	name->setStyleSheet("color: white; font-size: 20px ");

	testButton = new QPushButton("test", AlarmClockWidgetClass);

	gBoxLayout->addWidget(time, 0, 0);
	gBoxLayout->addWidget(name, 1, 0);
	gBoxLayout->addWidget(testButton, 0, 1);

	AlarmClockWidgetClass->setLayout(gBoxLayout);

	QMetaObject::connectSlotsByName(AlarmClockWidgetClass);
}
