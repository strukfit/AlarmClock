#include "MainWindowUI.h"

void MainWindowUI::setupUI(QMainWindow* MainWindow)
{
	MainWindow->resize(600, 500);
	MainWindow->setMinimumSize(566, 187);

	centralWidget = new QWidget(MainWindow);
	centralWidget->setStyleSheet("background-color: #272727;");

	centralLayout = new QHBoxLayout(centralWidget);
	centralLayout->setContentsMargins(48, 0, 0, 0);
	centralLayout->setSpacing(0);

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
	alarmsWidget = new ResizableWidget(centralWidget);
	alarmsWidget->setContentsMargins(0, 0, 0, 0);

	alarmVLayout = new QVBoxLayout(alarmsWidget);
	alarmVLayout->setContentsMargins(0, 0, 0, 0);

	alarmsChildWidget = new QWidget(alarmsWidget);
	alarmsChildWidget->setContentsMargins(0, 0, 0, 0);

	alarmsChildLayout = new QVBoxLayout(alarmsChildWidget);
	alarmsChildLayout->setContentsMargins(0, 0, 0, 0);

	QScrollArea* scrollArea = new QScrollArea(alarmsChildWidget);
	CustomScrollBar* scrollBar = new CustomScrollBar(alarmsChildWidget);
	scrollBar->setSingleStep(5);
	scrollArea->setVerticalScrollBar(scrollBar);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QWidget* scrollAreaWidgetContents = new QWidget();

	alarmsListLayout = new QVBoxLayout(scrollAreaWidgetContents);
	alarmsListLayout->setContentsMargins(48, 22, 48, 22);
	alarmsListLayout->setSpacing(14);

	scrollArea->setWidget(scrollAreaWidgetContents);

	alarmsChildLayout->addWidget(scrollArea);

	alarmVLayout->addWidget(alarmsChildWidget);

	alarmsManagerWidget = new QWidget(alarmsWidget);
	alarmsManagerWidget->setStyleSheet("background-color: #2C2C2C; border: 1px solid #404040; border-radius: 10px;");

	auto shadowEffect = new QGraphicsDropShadowEffect;
	shadowEffect->setBlurRadius(20);
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setOffset(3, 7);

	alarmsManagerWidget->setGraphicsEffect(shadowEffect);
	alarmsManagerWidget->setFixedSize(QSize(88, 48));

	QObject::connect(alarmsWidget, &ResizableWidget::resized, [&] {
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
	timerWidget = new ResizableWidget(centralWidget);
	timerWidget->setContentsMargins(0, 0, 0, 0);

	timerLayout = new QVBoxLayout(timerWidget);
	timerLayout->setContentsMargins(0, 0, 0, 0);

	timerChildWidget = new QWidget(timerWidget);
	timerChildWidget->setContentsMargins(0, 0, 0, 0);

	timerChildLayout = new QVBoxLayout(timerChildWidget);
	timerChildLayout->setContentsMargins(0, 0, 0, 0);

	QScrollArea* scrollArea = new QScrollArea(timerChildWidget);
	CustomScrollBar* scrollBar = new CustomScrollBar(timerChildWidget);
	scrollBar->setSingleStep(5);
	scrollArea->setVerticalScrollBar(scrollBar);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QWidget* scrollAreaWidgetContents = new QWidget();

	timerListLayout = new QVBoxLayout(scrollAreaWidgetContents);
	timerListLayout->setContentsMargins(48, 22, 48, 22);
	timerListLayout->setSpacing(14);

	scrollArea->setWidget(scrollAreaWidgetContents);

	timerChildLayout->addWidget(scrollArea);

	timerLayout->addWidget(timerChildWidget);

	timerManagerWidget = new QWidget(timerWidget);
	timerManagerWidget->setStyleSheet("background-color: #2C2C2C; border: 1px solid #404040; border-radius: 10px;");

	auto shadowEffect = new QGraphicsDropShadowEffect;
	shadowEffect->setBlurRadius(20);
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setOffset(3, 7);

	timerManagerWidget->setGraphicsEffect(shadowEffect);
	timerManagerWidget->setFixedSize(QSize(88, 48));

	QObject::connect(timerWidget, &ResizableWidget::resized, [&] {
		timerManagerWidget->move(timerWidget->geometry().width() - timerManagerWidget->width() - 24, timerWidget->geometry().height() - timerManagerWidget->height() - 20);
	});

	timerManagerLayout = new QHBoxLayout(timerManagerWidget);
	timerManagerLayout->setContentsMargins(6, 0, 6, 0);

	deleteTimerButton = new IconPushButton(timerManagerWidget, "", "transparent", "transparent", "Resources/pen-white.svg", "Resources/pen-grey.svg", "transparent", "#383838", "#343434");
	deleteTimerButton->setFixedSize(QSize(36, 36));
	deleteTimerButton->setIconSize(QSize(20, 20));

	timerConfirmButton = new IconPushButton(timerManagerWidget, "", "transparent", "transparent", "Resources/confirm-white.svg", "Resources/confirm-grey.svg", "transparent", "#383838", "#343434");
	timerConfirmButton->setFixedSize(QSize(36, 36));
	timerConfirmButton->setIconSize(QSize(16, 16));

	timerAddButton = new IconPushButton(timerManagerWidget, "", "transparent", "transparent", "Resources/add-white.svg", "Resources/add-grey.svg", "transparent", "#383838", "#343434");
	timerAddButton->setFixedSize(QSize(36, 36));
	timerAddButton->setIconSize(QSize(20, 20));

	timerManagerLayout->addWidget(deleteTimerButton);
	timerManagerLayout->addWidget(timerConfirmButton);
	timerConfirmButton->hide();
	timerManagerLayout->addWidget(timerAddButton);

	centralLayout->addWidget(timerWidget);

	timerWidget->hide();
}

void MainWindowUI::setupStopwatchUI()
{
	stopwatchWidget = new QWidget(centralWidget);
	stopwatchWidget->setContentsMargins(0, 0, 0, 0);

	stopwatchLayout = new QVBoxLayout(stopwatchWidget);
	stopwatchLayout->setContentsMargins(0, 55, 0, 0);
	stopwatchLayout->setAlignment(Qt::AlignCenter);
	stopwatchLayout->setSpacing(0);

	stopwatchLabel = new QLabel(QString("<span style=\"font-size: 80pt; \">00:00:00,</span><span style=\"font-size: 60pt;\">00</span>"), stopwatchWidget);
	stopwatchLabel->setStyleSheet("color: #CECECE;");
	stopwatchLabel->setFixedHeight(125);
	stopwatchLabel->setAlignment(Qt::AlignCenter);

	stopwatchLayout->addWidget(stopwatchLabel);

	hLabel = new QLabel("h");
	hLabel->setStyleSheet("color: #CECECE; font-size: 20px;");

	mLabel = new QLabel("min");
	mLabel->setStyleSheet("color: #CECECE; font-size: 20px;");

	sLabel = new QLabel("s");
	sLabel->setStyleSheet("color: #CECECE; font-size: 20px;");

	auto timeUnitsLayout = new QHBoxLayout(stopwatchWidget);
	timeUnitsLayout->setContentsMargins(27, 0, 139, 0);
	timeUnitsLayout->setSpacing(116);

	timeUnitsLayout->addStretch();
	timeUnitsLayout->addWidget(hLabel);
	timeUnitsLayout->addWidget(mLabel);
	timeUnitsLayout->addWidget(sLabel);
	timeUnitsLayout->addStretch();

	stopwatchLayout->addLayout(timeUnitsLayout);

	startButton = new IconPushButton(stopwatchWidget, "", "", "", "Resources/play-black.svg", "Resources/play-light.svg", "#76B9ED", "#6FABDA", "#679DC6", 35, "Resources/play-inactive.svg");
	startButton->setFixedSize(QSize(70, 70));
	startButton->setIconSize(QSize(23, 23));
	startButton->setStyleSheet(startButton->styleSheet().append(R"(
		QPushButton:disabled {
			background-color: #525252;
		}
	)"));

	pauseButton = new IconPushButton(stopwatchWidget, "", "", "", "Resources/pause-black.svg", "Resources/pause-light.svg", "#76B9ED", "#6FABDA", "#679DC6", 35, "Resources/pause-inactive.svg");
	pauseButton->setFixedSize(QSize(70, 70));
	pauseButton->setIconSize(QSize(23, 23));
	pauseButton->setStyleSheet(pauseButton->styleSheet().append(R"(
		QPushButton:disabled {
			background-color: #525252;
		}
	)"));
	pauseButton->hide();

	resetButton = new IconPushButton(stopwatchWidget, "", "", "", "Resources/restart-white.svg", "Resources/restart-grey.svg", "#3B3B3B", "#3b3b3b", "#363636", 35, "Resources/restart-inactive.svg");
	resetButton->setFixedSize(QSize(70, 70));
	resetButton->setIconSize(QSize(35, 35));
	resetButton->setStyleSheet(resetButton->styleSheet().append("QPushButton { border: 1px solid #474747; }"));

	cutoffButton = new IconPushButton(stopwatchWidget, "", "", "", "Resources/flag-white.svg", "Resources/flag-grey.svg", "#3B3B3B", "#3b3b3b", "#363636", 35, "Resources/flag-inactive.svg");
	cutoffButton->setFixedSize(QSize(70, 70));
	cutoffButton->setIconSize(QSize(35, 35));
	cutoffButton->setStyleSheet(cutoffButton->styleSheet().append(R"( QPushButton { border: 1px solid #474747; })"));
	cutoffButton->setDisabled(true);
	cutoffButton->setInactiveIcon(true);

	auto buttonsLayout = new QHBoxLayout(stopwatchWidget);
	buttonsLayout->setSpacing(24);

	buttonsLayout->addStretch();
	buttonsLayout->addWidget(startButton);
	buttonsLayout->addWidget(pauseButton);
	buttonsLayout->addWidget(cutoffButton);
	buttonsLayout->addWidget(resetButton);
	buttonsLayout->addStretch();

	stopwatchLayout->addSpacing(48);
	stopwatchLayout->addLayout(buttonsLayout);
	//stopwatchLayout->addStretch();

	cutoffTable = new QTableWidget(stopwatchWidget);
	cutoffTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	cutoffTable->setFocusPolicy(Qt::NoFocus);
	cutoffTable->setSelectionMode(QAbstractItemView::NoSelection);
	cutoffTable->setColumnCount(3);
	QStringList columns = {"Circle time", "Time", "Total"};
	cutoffTable->setHorizontalHeaderLabels(columns);
	cutoffTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	cutoffTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	cutoffTable->setMaximumWidth(664);
	cutoffTable->setMinimumWidth(536);
	CustomScrollBar* scrollBar = new CustomScrollBar(stopwatchWidget);
	scrollBar->setSingleStep(5);
	cutoffTable->setVerticalScrollBar(scrollBar);
	cutoffTable->setStyleSheet(R"(
		QTableWidget {
			background-color: #272727;
			gridline-color: transparent;
			/*height: 60px;*/
			color: white;
			font-size: 14px;
			border: none;
		}

		QHeaderView::section {
			background-color: #272727;
			color: white;
			font-size: 14px;
			font-weight: bold;
			border-style: none;
			border-bottom: 2px solid #393939;
		}

		QTableView QTableCornerButton::section {
			background-color: #272727;
			border-style: none;
		}
	)");
	cutoffTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	cutoffTable->verticalHeader()->setDefaultSectionSize(43);
	cutoffTable->verticalHeader()->hide();
	cutoffTable->hide();

	auto cutoffTableLayout = new QHBoxLayout(stopwatchWidget);
	cutoffTableLayout->setContentsMargins(0, 0, 0, 0);
	cutoffTableLayout->setSpacing(0);
	cutoffTableLayout->addWidget(cutoffTable);

	stopwatchLayout->addSpacing(32);
	stopwatchLayout->addLayout(cutoffTableLayout);
	stopwatchLayout->addStretch();

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