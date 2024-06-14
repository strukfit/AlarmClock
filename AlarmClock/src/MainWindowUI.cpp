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

	MenuUI.centralWidget = new QWidget(centralWidget);
	MenuUI.centralWidget->setStyleSheet("background-color: #202020;");
	MenuUI.centralWidget->setFixedWidth(48);

	auto functionSelectorLayout = new QVBoxLayout(MenuUI.centralWidget);
	functionSelectorLayout->setContentsMargins(3, 3, 3, 0);
	functionSelectorLayout->setSpacing(5);

	MenuUI.menuButton = new IconPushButton(MenuUI.centralWidget, "", "white", "#c1c1c1", "Resources/side-menu-white.svg", "Resources/side-menu-grey.svg", "transparent", "#383838", "#343434");
	MenuUI.menuButton->setFixedSize(40, 32);
	MenuUI.menuButton->setIconSize(QSize(18, 23));
	
	functionSelectorLayout->addWidget(MenuUI.menuButton);

	MenuUI.alarmClockButton = new CheckableButton(MenuUI.centralWidget, "", "white", "#c1c1c1", "Resources/alarm-white.svg", "Resources/alarm-grey.svg", "transparent", "#383838", "#343434");
	MenuUI.alarmClockButton->setFixedHeight(36);
	MenuUI.alarmClockButton->setMinimumWidth(40);
	//alarmClockButton->setIconSize(QSize(15, 15));
	MenuUI.alarmClockButton->setStyleSheet(MenuUI.alarmClockButton->styleSheet().append("QPushButton { text-align: left; padding-left: 13px; }"));
	
	MenuUI.timerButton = new CheckableButton(MenuUI.centralWidget, "", "white", "#c1c1c1", "Resources/timer-white.svg", "Resources/timer-grey.svg", "transparent", "#383838", "#343434");
	MenuUI.timerButton->setFixedHeight(36);
	MenuUI.timerButton->setMinimumWidth(40);
	//timerButton->setIconSize(QSize(22, 20));
	MenuUI.timerButton->setStyleSheet(MenuUI.timerButton->styleSheet().append("QPushButton { text-align: left; padding-left: 13px; }"));

	MenuUI.stopwatchButton = new CheckableButton(MenuUI.centralWidget, "", "white", "#c1c1c1", "Resources/stopwatch-white.svg", "Resources/stopwatch-grey.svg", "transparent", "#383838", "#343434");
	MenuUI.stopwatchButton->setFixedHeight(36);
	MenuUI.stopwatchButton->setMinimumWidth(40);
	MenuUI.stopwatchButton->setIconSize(QSize(18, 18));
	MenuUI.stopwatchButton->setStyleSheet(MenuUI.stopwatchButton->styleSheet().append("QPushButton { text-align: left; padding-left: 13px; }"));

	MenuUI.worldClockButton = new CheckableButton(MenuUI.centralWidget, "", "white", "#c1c1c1", "Resources/world-clock-white.svg", "Resources/world-clock-grey.svg", "transparent", "#383838", "#343434");
	MenuUI.worldClockButton->setFixedHeight(36);
	MenuUI.worldClockButton->setMinimumWidth(40);
	MenuUI.worldClockButton->setStyleSheet(MenuUI.worldClockButton->styleSheet().append("QPushButton { text-align: left; padding-left: 13px; }"));

	MenuUI.alarmClockButton->setChecked(true);

	functionSelectorLayout->addWidget(MenuUI.alarmClockButton);
	functionSelectorLayout->addWidget(MenuUI.timerButton);
	functionSelectorLayout->addWidget(MenuUI.stopwatchButton);
	functionSelectorLayout->addWidget(MenuUI.worldClockButton);
	functionSelectorLayout->addStretch(0);

	MainWindow->setCentralWidget(centralWidget);

	QMetaObject::connectSlotsByName(MainWindow);
}

void MainWindowUI::setupAlarmClockUI()
{
	auto& ui = AlarmClockUI;

	ui.centralWidget = new ResizableWidget(centralWidget);
	ui.centralWidget->setContentsMargins(0, 0, 0, 0);

	ui.layout = new QVBoxLayout(ui.centralWidget);
	ui.layout->setContentsMargins(0, 0, 0, 0);

	ui.childWidget = new QWidget(ui.centralWidget);
	ui.childWidget->setContentsMargins(0, 0, 0, 0);

	ui.childLayout = new QVBoxLayout(ui.childWidget);
	ui.childLayout->setContentsMargins(0, 0, 0, 0);

	QScrollArea* scrollArea = new QScrollArea(ui.childWidget);
	CustomScrollBar* scrollBar = new CustomScrollBar(ui.childWidget);
	scrollBar->setSingleStep(5);
	scrollArea->setVerticalScrollBar(scrollBar);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QWidget* scrollAreaWidgetContents = new QWidget();

	ui.listLayout = new QVBoxLayout(scrollAreaWidgetContents);
	ui.listLayout->setContentsMargins(48, 22, 48, 22);
	ui.listLayout->setSpacing(14);

	scrollArea->setWidget(scrollAreaWidgetContents);

	ui.childLayout->addWidget(scrollArea);

	ui.layout->addWidget(ui.childWidget);

	ui.managerWidget = new QWidget(ui.centralWidget);
	ui.managerWidget->setStyleSheet("background-color: #2C2C2C; border: 1px solid #404040; border-radius: 10px;");

	auto shadowEffect = new QGraphicsDropShadowEffect;
	shadowEffect->setBlurRadius(20);
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setOffset(3, 7);

	ui.managerWidget->setGraphicsEffect(shadowEffect);
	ui.managerWidget->setFixedSize(QSize(88, 48));

	QObject::connect(ui.centralWidget, &ResizableWidget::resized, [&] {
		ui.managerWidget->move(ui.centralWidget->geometry().width() - ui.managerWidget->width() - 24, ui.centralWidget->geometry().height() - ui.managerWidget->height() - 20);
		});

	ui.managerLayout = new QHBoxLayout(ui.managerWidget);
	ui.managerLayout->setContentsMargins(6, 0, 6, 0);

	ui.deleteButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/pen-white.svg", "Resources/pen-grey.svg", "transparent", "#383838", "#343434");
	ui.deleteButton->setFixedSize(QSize(36, 36));
	ui.deleteButton->setIconSize(QSize(20, 20));

	ui.confirmButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/confirm-white.svg", "Resources/confirm-grey.svg", "transparent", "#383838", "#343434");
	ui.confirmButton->setFixedSize(QSize(36, 36));
	ui.confirmButton->setIconSize(QSize(16, 16));

	ui.addButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/add-white.svg", "Resources/add-grey.svg", "transparent", "#383838", "#343434");
	ui.addButton->setFixedSize(QSize(36, 36));
	ui.addButton->setIconSize(QSize(20, 20));

	ui.managerLayout->addWidget(ui.deleteButton);
	ui.managerLayout->addWidget(ui.confirmButton);
	ui.confirmButton->hide();
	ui.managerLayout->addWidget(ui.addButton);

	centralLayout->addWidget(ui.centralWidget);
}

void MainWindowUI::setupTimerUI()
{
	auto& ui = TimerUI;

	ui.centralWidget = new ResizableWidget(centralWidget);
	ui.centralWidget->setContentsMargins(0, 0, 0, 0);

	ui.layout = new QVBoxLayout(ui.centralWidget);
	ui.layout->setContentsMargins(0, 0, 0, 0);

	ui.childWidget = new QWidget(ui.centralWidget);
	ui.childWidget->setContentsMargins(0, 0, 0, 0);

	ui.childLayout = new QVBoxLayout(ui.childWidget);
	ui.childLayout->setContentsMargins(0, 0, 0, 0);

	QScrollArea* scrollArea = new QScrollArea(ui.childWidget);
	CustomScrollBar* scrollBar = new CustomScrollBar(ui.childWidget);
	scrollBar->setSingleStep(5);
	scrollArea->setVerticalScrollBar(scrollBar);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QWidget* scrollAreaWidgetContents = new QWidget();

	ui.listLayout = new QVBoxLayout(scrollAreaWidgetContents);
	ui.listLayout->setContentsMargins(48, 22, 48, 22);
	ui.listLayout->setSpacing(14);

	scrollArea->setWidget(scrollAreaWidgetContents);

	ui.childLayout->addWidget(scrollArea);

	ui.layout->addWidget(ui.childWidget);

	ui.managerWidget = new QWidget(ui.centralWidget);
	ui.managerWidget->setStyleSheet("background-color: #2C2C2C; border: 1px solid #404040; border-radius: 10px;");

	auto shadowEffect = new QGraphicsDropShadowEffect;
	shadowEffect->setBlurRadius(20);
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setOffset(3, 7);

	ui.managerWidget->setGraphicsEffect(shadowEffect);
	ui.managerWidget->setFixedSize(QSize(88, 48));

	QObject::connect(ui.centralWidget, &ResizableWidget::resized, [&] {
		ui.managerWidget->move(ui.centralWidget->geometry().width() - ui.managerWidget->width() - 24, ui.centralWidget->geometry().height() - ui.managerWidget->height() - 20);
	});

	ui.managerLayout = new QHBoxLayout(ui.managerWidget);
	ui.managerLayout->setContentsMargins(6, 0, 6, 0);

	ui.deleteButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/pen-white.svg", "Resources/pen-grey.svg", "transparent", "#383838", "#343434");
	ui.deleteButton->setFixedSize(QSize(36, 36));
	ui.deleteButton->setIconSize(QSize(20, 20));

	ui.confirmButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/confirm-white.svg", "Resources/confirm-grey.svg", "transparent", "#383838", "#343434");
	ui.confirmButton->setFixedSize(QSize(36, 36));
	ui.confirmButton->setIconSize(QSize(16, 16));

	ui.addButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/add-white.svg", "Resources/add-grey.svg", "transparent", "#383838", "#343434");
	ui.addButton->setFixedSize(QSize(36, 36));
	ui.addButton->setIconSize(QSize(20, 20));

	ui.managerLayout->addWidget(ui.deleteButton);
	ui.managerLayout->addWidget(ui.confirmButton);
	ui.confirmButton->hide();
	ui.managerLayout->addWidget(ui.addButton);

	centralLayout->addWidget(ui.centralWidget);

	ui.centralWidget->hide();
}

void MainWindowUI::setupStopwatchUI()
{
	auto& ui = StopwatchUI;

	ui.centralWidget = new QWidget(centralWidget);
	ui.centralWidget->setContentsMargins(0, 0, 0, 0);

	ui.layout = new QVBoxLayout(ui.centralWidget);
	ui.layout->setContentsMargins(0, 55, 0, 0);
	ui.layout->setAlignment(Qt::AlignCenter);
	ui.layout->setSpacing(0);

	ui.label = new QLabel(QString("<span style=\"font-size: 80pt; \">00:00:00,</span><span style=\"font-size: 60pt;\">00</span>"), ui.centralWidget);
	ui.label->setStyleSheet("color: #CECECE;");
	ui.label->setFixedHeight(125);
	ui.label->setAlignment(Qt::AlignCenter);

	ui.layout->addWidget(ui.label);

	ui.hLabel = new QLabel("h");
	ui.hLabel->setStyleSheet("color: #CECECE; font-size: 20px;");

	ui.mLabel = new QLabel("min");
	ui.mLabel->setStyleSheet("color: #CECECE; font-size: 20px;");

	ui.sLabel = new QLabel("s");
	ui.sLabel->setStyleSheet("color: #CECECE; font-size: 20px;");

	auto timeUnitsLayout = new QHBoxLayout(ui.centralWidget);
	timeUnitsLayout->setContentsMargins(27, 0, 139, 0);
	timeUnitsLayout->setSpacing(116);

	timeUnitsLayout->addStretch();
	timeUnitsLayout->addWidget(ui.hLabel);
	timeUnitsLayout->addWidget(ui.mLabel);
	timeUnitsLayout->addWidget(ui.sLabel);
	timeUnitsLayout->addStretch();

	ui.layout->addLayout(timeUnitsLayout);

	ui.startButton = new IconPushButton(ui.centralWidget, "", "", "", "Resources/play-black.svg", "Resources/play-light.svg", "#76B9ED", "#6FABDA", "#679DC6", 35, "Resources/play-inactive.svg");
	ui.startButton->setFixedSize(QSize(70, 70));
	ui.startButton->setIconSize(QSize(23, 23));
	ui.startButton->setStyleSheet(ui.startButton->styleSheet().append(R"(
		QPushButton:disabled {
			background-color: #525252;
		}
	)"));

	ui.pauseButton = new IconPushButton(ui.centralWidget, "", "", "", "Resources/pause-black.svg", "Resources/pause-light.svg", "#76B9ED", "#6FABDA", "#679DC6", 35, "Resources/pause-inactive.svg");
	ui.pauseButton->setFixedSize(QSize(70, 70));
	ui.pauseButton->setIconSize(QSize(23, 23));
	ui.pauseButton->setStyleSheet(ui.pauseButton->styleSheet().append(R"(
		QPushButton:disabled {
			background-color: #525252;
		}
	)"));
	ui.pauseButton->hide();

	ui.resetButton = new IconPushButton(ui.centralWidget, "", "", "", "Resources/restart-white.svg", "Resources/restart-grey.svg", "#3B3B3B", "#3b3b3b", "#363636", 35, "Resources/restart-inactive.svg");
	ui.resetButton->setFixedSize(QSize(70, 70));
	ui.resetButton->setIconSize(QSize(35, 35));
	ui.resetButton->setStyleSheet(ui.resetButton->styleSheet().append("QPushButton { border: 1px solid #474747; }"));

	ui.cutoffButton = new IconPushButton(ui.centralWidget, "", "", "", "Resources/flag-white.svg", "Resources/flag-grey.svg", "#3B3B3B", "#3b3b3b", "#363636", 35, "Resources/flag-inactive.svg");
	ui.cutoffButton->setFixedSize(QSize(70, 70));
	ui.cutoffButton->setIconSize(QSize(35, 35));
	ui.cutoffButton->setStyleSheet(ui.cutoffButton->styleSheet().append(R"( QPushButton { border: 1px solid #474747; })"));
	ui.cutoffButton->setDisabled(true);
	ui.cutoffButton->setInactiveIcon(true);

	auto buttonsLayout = new QHBoxLayout(ui.centralWidget);
	buttonsLayout->setSpacing(24);

	buttonsLayout->addStretch();
	buttonsLayout->addWidget(ui.startButton);
	buttonsLayout->addWidget(ui.pauseButton);
	buttonsLayout->addWidget(ui.cutoffButton);
	buttonsLayout->addWidget(ui.resetButton);
	buttonsLayout->addStretch();

	ui.layout->addSpacing(48);
	ui.layout->addLayout(buttonsLayout);

	ui.cutoffTable = new QTableWidget(ui.centralWidget);
	ui.cutoffTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.cutoffTable->setFocusPolicy(Qt::NoFocus);
	ui.cutoffTable->setSelectionMode(QAbstractItemView::NoSelection);
	ui.cutoffTable->setColumnCount(3);
	QStringList columns = {"Circle time", "Time", "Total"};
	ui.cutoffTable->setHorizontalHeaderLabels(columns);
	ui.cutoffTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui.cutoffTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.cutoffTable->setMaximumWidth(664);
	ui.cutoffTable->setMinimumWidth(536);
	CustomScrollBar* scrollBar = new CustomScrollBar(ui.centralWidget);
	scrollBar->setSingleStep(5);
	ui.cutoffTable->setVerticalScrollBar(scrollBar);
	ui.cutoffTable->setStyleSheet(R"(
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
	ui.cutoffTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui.cutoffTable->verticalHeader()->setDefaultSectionSize(43);
	ui.cutoffTable->verticalHeader()->hide();
	ui.cutoffTable->hide();

	auto cutoffTableLayout = new QHBoxLayout(ui.centralWidget);
	cutoffTableLayout->setContentsMargins(0, 0, 0, 0);
	cutoffTableLayout->setSpacing(0);
	cutoffTableLayout->addWidget(ui.cutoffTable);

	ui.layout->addSpacing(32);
	ui.layout->addLayout(cutoffTableLayout);
	ui.layout->addStretch();

	centralLayout->addWidget(ui.centralWidget);

	ui.centralWidget->hide();
}

void MainWindowUI::setupWorldClockUI()
{
	auto& ui = WorldClockUI;

	ui.centralWidget = new ResizableWidget(centralWidget);
	ui.centralWidget->setContentsMargins(0, 0, 0, 0);

	ui.layout = new QVBoxLayout(ui.centralWidget);
	ui.layout->setAlignment(Qt::AlignCenter);
	ui.layout->setContentsMargins(0, 0, 0, 0);

	ui.childWidget = new QWidget(ui.centralWidget);
	ui.childWidget->setContentsMargins(0, 0, 0, 0);

	ui.childLayout = new QVBoxLayout(ui.childWidget);
	ui.childLayout->setContentsMargins(0, 0, 0, 0);

	QScrollArea* scrollArea = new QScrollArea(ui.childWidget);
	CustomScrollBar* scrollBar = new CustomScrollBar(ui.childWidget);
	scrollBar->setSingleStep(5);
	scrollArea->setVerticalScrollBar(scrollBar);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QWidget* scrollAreaWidgetContents = new QWidget();

	ui.listLayout = new QVBoxLayout(scrollAreaWidgetContents);
	ui.listLayout->setContentsMargins(64, 24, 64, 24);
	ui.listLayout->setSpacing(14);

	auto systemClock = new ClockWidget(centralWidget, 0, QTimeZone::systemTimeZoneId());
	ui.listLayout->addWidget(systemClock);

	scrollArea->setWidget(scrollAreaWidgetContents);

	ui.childLayout->addWidget(scrollArea);

	ui.layout->addWidget(ui.childWidget);

	ui.managerWidget = new QWidget(ui.centralWidget);
	ui.managerWidget->setStyleSheet("background-color: #2C2C2C; border: 1px solid #404040; border-radius: 10px;");

	auto shadowEffect = new QGraphicsDropShadowEffect;
	shadowEffect->setBlurRadius(20);
	shadowEffect->setColor(QColor(0, 0, 0, 30));
	shadowEffect->setOffset(3, 7);

	ui.managerWidget->setGraphicsEffect(shadowEffect);
	ui.managerWidget->setFixedSize(QSize(88, 48));

	QObject::connect(ui.centralWidget, &ResizableWidget::resized, [&] {
		ui.managerWidget->move(ui.centralWidget->geometry().width() - ui.managerWidget->width() - 24, ui.centralWidget->geometry().height() - ui.managerWidget->height() - 20);
		});

	ui.managerLayout = new QHBoxLayout(ui.managerWidget);
	ui.managerLayout->setContentsMargins(6, 0, 6, 0);

	ui.deleteButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/pen-white.svg", "Resources/pen-grey.svg", "transparent", "#383838", "#343434");
	ui.deleteButton->setFixedSize(QSize(36, 36));
	ui.deleteButton->setIconSize(QSize(20, 20));

	ui.confirmButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/confirm-white.svg", "Resources/confirm-grey.svg", "transparent", "#383838", "#343434");
	ui.confirmButton->setFixedSize(QSize(36, 36));
	ui.confirmButton->setIconSize(QSize(16, 16));

	ui.addButton = new IconPushButton(ui.managerWidget, "", "transparent", "transparent", "Resources/add-white.svg", "Resources/add-grey.svg", "transparent", "#383838", "#343434");
	ui.addButton->setFixedSize(QSize(36, 36));
	ui.addButton->setIconSize(QSize(20, 20));

	ui.managerLayout->addWidget(ui.deleteButton);
	ui.managerLayout->addWidget(ui.confirmButton);
	ui.confirmButton->hide();
	ui.managerLayout->addWidget(ui.addButton);

	centralLayout->addWidget(ui.centralWidget);
	ui.centralWidget->hide();
}