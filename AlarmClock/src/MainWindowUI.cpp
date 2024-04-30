#include "MainWindowUI.h"

void MainWindowUI::setupUI(QMainWindow* MainWindow)
{
	MainWindow->resize(600, 500);
	MainWindow->setMinimumSize(400, 187);

	centralWidget = new QWidget(MainWindow);
	centralWidget->setStyleSheet("background-color: #272727;");

	centralLayout = new QHBoxLayout(centralWidget);
	centralLayout->setContentsMargins(48, 0, 0, 0);
	centralLayout->setSpacing(0);

	//centralLayout->addWidget(functionSelectorWidget);

	setupAlarmClockUI();
	setupTimerUI();
	setupStopwatchUI();
	setupWorldClockUI();

	functionSelectorWidget = new QWidget(centralWidget);
	functionSelectorWidget->setStyleSheet("background-color: #202020;");
	functionSelectorWidget->setFixedWidth(48);

	QVBoxLayout* functionSelectorLayout = new QVBoxLayout(functionSelectorWidget);
	functionSelectorLayout->setContentsMargins(3, 3, 3, 0);
	functionSelectorLayout->setSpacing(5);
	//functionSelectorLayout->setAlignment(Qt::AlignCenter);

	menuButton = new IconPushButton(functionSelectorWidget, "", "white", "#c1c1c1", "Resources/side-menu-white.svg", "Resources/side-menu-grey.svg", "transparent", "#383838", "#343434");
	menuButton->setFixedSize(40, 32);
	menuButton->setIconSize(QSize(18, 23));
	
	functionSelectorLayout->addWidget(menuButton);

	alarmClockButton = new CheckableButton(functionSelectorWidget, "", "white", "#c1c1c1", "Resources/alarm-white.svg", "Resources/alarm-grey.svg", "transparent", "#383838", "#343434");
	alarmClockButton->setFixedHeight(36);
	alarmClockButton->setMinimumWidth(40);
	//alarmClockButton->setIconSize(QSize(15, 15));
	alarmClockButton->setStyleSheet(alarmClockButton->styleSheet().append("QPushButton { text-align: left; padding-left: 13px; }"));
	
	timerButton = new CheckableButton(functionSelectorWidget, "", "white", "#c1c1c1", "Resources/timer-white.svg", "Resources/timer-grey.svg", "transparent", "#383838", "#343434");
	timerButton->setFixedHeight(36);
	timerButton->setMinimumWidth(40);
	//timerButton->setIconSize(QSize(22, 20));
	timerButton->setStyleSheet(timerButton->styleSheet().append("QPushButton { text-align: left; padding-left: 13px; }"));

	stopwatchButton = new CheckableButton(functionSelectorWidget, "", "white", "#c1c1c1", "Resources/stopwatch-white.svg", "Resources/stopwatch-grey.svg", "transparent", "#383838", "#343434");
	stopwatchButton->setFixedHeight(36);
	stopwatchButton->setMinimumWidth(40);
	stopwatchButton->setIconSize(QSize(18, 18));
	stopwatchButton->setStyleSheet(stopwatchButton->styleSheet().append("QPushButton { text-align: left; padding-left: 13px; }"));

	worldClockButton = new CheckableButton(functionSelectorWidget, "", "white", "#c1c1c1", "Resources/world-clock-white.svg", "Resources/world-clock-grey.svg", "transparent", "#383838", "#343434");
	worldClockButton->setFixedHeight(36);
	worldClockButton->setMinimumWidth(40);
	//worldClockButton->setIconSize(QSize(16, 16));
	worldClockButton->setStyleSheet(worldClockButton->styleSheet().append("QPushButton { text-align: left; padding-left: 13px; }"));

	alarmClockButton->setChecked(true);

	functionSelectorLayout->addWidget(alarmClockButton);
	functionSelectorLayout->addWidget(timerButton);
	functionSelectorLayout->addWidget(stopwatchButton);
	functionSelectorLayout->addWidget(worldClockButton);
	functionSelectorLayout->addStretch(0);

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
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

void MainWindowUI::setupTimerUI()
{
	timerWidget = new QWidget(centralWidget);

	timerLayout = new QVBoxLayout(timerWidget);
	timerLayout->setAlignment(Qt::AlignCenter);

	timerLabel = new QLabel("Timer", timerWidget);
	timerLabel->setAlignment(Qt::AlignCenter);

	timerLayout->addWidget(timerLabel);

	centralLayout->addWidget(timerWidget);

	timerWidget->hide();
}

void MainWindowUI::setupStopwatchUI()
{
	stopwatchWidget = new QWidget(centralWidget);

	stopwatchLayout = new QVBoxLayout(stopwatchWidget);
	stopwatchLayout->setAlignment(Qt::AlignCenter);

	stopwatchLabel = new QLabel("Stopwatch", stopwatchWidget);
	stopwatchLabel->setAlignment(Qt::AlignCenter);

	stopwatchLayout->addWidget(stopwatchLabel);

	centralLayout->addWidget(stopwatchWidget);

	stopwatchWidget->hide();
}

void MainWindowUI::setupWorldClockUI()
{
	worldClockWidget = new QWidget(centralWidget);

	worldClockLayout = new QVBoxLayout(worldClockWidget);
	worldClockLayout->setAlignment(Qt::AlignCenter);

	worldClockLabel = new QLabel("World clock", worldClockWidget);
	worldClockLabel->setAlignment(Qt::AlignCenter);

	worldClockLayout->addWidget(worldClockLabel);

	centralLayout->addWidget(worldClockWidget);

	worldClockWidget->hide();
}