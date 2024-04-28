#include "MainWindowUI.h"

void MainWindowUI::setupUI(QMainWindow* MainWindow)
{
	MainWindow->resize(600, 500);

	centralWidget = new QWidget(MainWindow);
	centralWidget->setStyleSheet("background-color: #272727;");

	centralLayout = new QHBoxLayout(centralWidget);
	centralLayout->setContentsMargins(0, 0, 0, 0);
	centralLayout->setSpacing(0);

	functionSelectorWidget = new QWidget(centralWidget);
	functionSelectorWidget->setStyleSheet("background-color: white;");
	functionSelectorWidget->setFixedWidth(48);

	centralLayout->addWidget(functionSelectorWidget);

	setupAlarmClockUI();

	MainWindow->setCentralWidget(centralWidget);

	QMetaObject::connectSlotsByName(MainWindow);
}

void MainWindowUI::setupAlarmClockUI()
{
	alarmsWidget = new AlarmsWidget(centralWidget);
	alarmsWidget->setContentsMargins(0, 0, 0, 0);

	verticalLayout = new QVBoxLayout(alarmsWidget);
	verticalLayout->setContentsMargins(0, 0, 0, 0);

	alarmsChildWidget = new QWidget(alarmsWidget);
	alarmsChildWidget->setContentsMargins(0, 0, 0, 0);

	alarmsChildLayout = new QVBoxLayout(alarmsChildWidget);
	alarmsChildLayout->setContentsMargins(0, 0, 0, 0);

	scrollArea = new QScrollArea(alarmsChildWidget);
	AlarmScrollBar* scrollBar = new AlarmScrollBar(alarmsChildWidget);
	scrollBar->setSingleStep(5);
	scrollArea->setVerticalScrollBar(scrollBar);
	scrollArea->setWidgetResizable(true);

	scrollAreaWidgetContents = new QWidget();

	alarmsListLayout = new QVBoxLayout(scrollAreaWidgetContents);
	alarmsListLayout->setContentsMargins(48, 22, 48, 22);
	alarmsListLayout->setSpacing(14);

	scrollArea->setWidget(scrollAreaWidgetContents);

	alarmsChildLayout->addWidget(scrollArea);

	verticalLayout->addWidget(alarmsChildWidget);

	alarmsManagerWidget = new QWidget(alarmsWidget);
	alarmsManagerWidget->setStyleSheet("background-color: #2C2C2C; border: 1px solid #404040; border-radius: 10px;");

	QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
	shadowEffect->setBlurRadius(20);
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setOffset(3, 7);

	alarmsManagerWidget->setGraphicsEffect(shadowEffect);
	alarmsManagerWidget->setFixedSize(QSize(88, 48));

	QObject::connect(alarmsWidget, &AlarmsWidget::resized, [&] {
		alarmsManagerWidget->move(alarmsWidget->geometry().width() - alarmsManagerWidget->width() - 24, alarmsWidget->geometry().height() - alarmsManagerWidget->height() - 20);
		});

	alarmsManagerLayout = new QHBoxLayout(alarmsManagerWidget);
	alarmsManagerLayout->setContentsMargins(6, 0, 6, 0);

	deleteAlarmsButton = new IconPushButton(alarmsManagerWidget, "", "transparent", "transparent", "Resources/pen-white.svg", "Resources/pen-grey.svg", "transparent", "#383838", "#343434");
	deleteAlarmsButton->setFixedSize(QSize(36, 36));
	deleteAlarmsButton->setIconSize(QSize(20, 20));

	confirmButton = new IconPushButton(alarmsManagerWidget, "", "transparent", "transparent", "Resources/confirm-white.svg", "Resources/confirm-grey.svg", "transparent", "#383838", "#343434");
	confirmButton->setFixedSize(QSize(36, 36));
	confirmButton->setIconSize(QSize(16, 16));

	addAlarmButton = new IconPushButton(alarmsManagerWidget, "", "transparent", "transparent", "Resources/add-white.svg", "Resources/add-grey.svg", "transparent", "#383838", "#343434");
	addAlarmButton->setFixedSize(QSize(36, 36));
	addAlarmButton->setIconSize(QSize(20, 20));

	alarmsManagerLayout->addWidget(deleteAlarmsButton);
	alarmsManagerLayout->addWidget(confirmButton);
	confirmButton->hide();
	alarmsManagerLayout->addWidget(addAlarmButton);

	centralLayout->addWidget(alarmsWidget);
}
