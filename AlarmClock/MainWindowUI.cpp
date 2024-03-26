#include "MainWindowUI.h"

MainWindowUI::~MainWindowUI()
{
	delete centralWidget;
	delete addAlarmButton;
	delete alarmsListWidget;
	delete vBoxLayout;
}

void MainWindowUI::setupMainWindowUI(QMainWindow* MainWindowClass)
{
	centralWidget = new QWidget(MainWindowClass);

	vBoxLayout = new QVBoxLayout(centralWidget);
	
	alarmsListWidget = new QListWidget(centralWidget);

	alarmsListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	alarmsListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	alarmsListWidget->setStyleSheet(R"(
		QListWidget::item { 
			background-color: #323232; 
			border-radius: 5px; 
			margin-left: 10px; 
			margin-right: 10px; 
			margin-bottom: 5px; 
			margin-top: 5px; 
		}
	)");

	addAlarmButton = new QPushButton("Add", centralWidget);
	addAlarmButton->setObjectName("addAlarmButton");

	vBoxLayout->addWidget(alarmsListWidget);
	vBoxLayout->addWidget(addAlarmButton);

	MainWindowClass->setLayout(vBoxLayout);

	MainWindowClass->setCentralWidget(centralWidget);

	QMetaObject::connectSlotsByName(MainWindowClass);
}