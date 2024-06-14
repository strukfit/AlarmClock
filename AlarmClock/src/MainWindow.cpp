#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), 
	ui(new Ui::MainWindowClass),
	menuExpanded(false),
	stopwatchTime(0),
	cutoffTime(0)
{
	ui->setupUI(this);

	overlayWidget = new QWidget(this);
	overlayWidget->setGeometry(geometry());
	overlayWidget->setStyleSheet("background-color: rgba(0, 0, 0, 0.75);");
	overlayWidget->hide();

	dbManager = new DatabaseManager(this);

	connect(dbManager, &DatabaseManager::alarmDataReceived, this, &MainWindow::setAlarm);
	connect(dbManager, &DatabaseManager::timerDataReceived, this, &MainWindow::setTimer);
	connect(dbManager, &DatabaseManager::clockDataReceived, this, &MainWindow::addClock);

	dbManager->open();

	dbManager->tableInit();

	dbManager->selectAllAlarms();
	dbManager->selectAllTimers();
	dbManager->selectAllClocks();

	AlarmClockWidget::lastId = dbManager->getLastAlarmId();
	TimerWidget::lastId = dbManager->getLastTimerId();
	ClockWidget::lastId = dbManager->getLastClockId();
	
	setSideMenuConnections();

	connect(this, &MainWindow::childWindowShowed, [&] {
		overlayWidget->resize(size());
		overlayWidget->show();
	});

	timer = new QTimer(this);
	setAlarmClockConnections();
	connect(timer, &QTimer::timeout, this, &MainWindow::checkAlarm);
	setTimerConnections();
	setStopwatchConnections();
	setWorldClockConnections();
	timer->start(1000);	
}

void MainWindow::stopwatchUpdateTime()
{
	QString timeString = QString("<span style=\"font-size: 80pt; \">00:00:00,</span><span style=\"font-size: 60pt;\">00</span>");

	if (this->stopwatchTimer->isActive()) {
		stopwatchTime += 10;
		cutoffTime += 10;
		int ms = stopwatchTime % 1000;
		int s = (stopwatchTime / 1000) % 60;
		int m = (stopwatchTime / (1000 * 60)) % 60;
		int h = (stopwatchTime / (1000 * 60 * 60)) % 24;
		timeString = QString("<span style=\"font-size: 80pt; \">%1:%2:%3,</span><span style=\"font-size: 60pt;\">%4</span>")
			.arg(h, 2, 10, QLatin1Char('0'))
			.arg(m, 2, 10, QLatin1Char('0'))
			.arg(s, 2, 10, QLatin1Char('0'))
			.arg(ms / 10, 2, 10, QLatin1Char('0'));
	}
	
	ui->StopwatchUI.label->setText(timeString); 
}

void MainWindow::cutoffTableCalculations()
{
	if (!this->stopwatchTimer->isActive())
		return;

	int sMs = stopwatchTime % 1000;
	int sS = (stopwatchTime / 1000) % 60;
	int sM = (stopwatchTime / (1000 * 60)) % 60;
	int sH = (stopwatchTime / (1000 * 60 * 60)) % 24;

	int cMs = cutoffTime % 1000;
	int cS = (cutoffTime / 1000) % 60;
	int cM = (cutoffTime / (1000 * 60)) % 60;
	int cH = (cutoffTime / (1000 * 60 * 60)) % 24;

	auto total = QString("%1:%2:%3,%4")
		.arg(sH, 2, 10, QLatin1Char('0'))
		.arg(sM, 2, 10, QLatin1Char('0'))
		.arg(sS, 2, 10, QLatin1Char('0'))
		.arg(sMs / 10, 2, 10, QLatin1Char('0'));

	auto cutoff = QString("%1:%2:%3,%4")
		.arg(cH, 2, 10, QLatin1Char('0'))
		.arg(cM, 2, 10, QLatin1Char('0'))
		.arg(cS, 2, 10, QLatin1Char('0'))
		.arg(cMs / 10, 2, 10, QLatin1Char('0'));

	auto totalItem = new QTableWidgetItem(total);

	auto cutoffItem = new QTableWidgetItem(cutoff);
	auto cutoffVariant = QVariant(cutoffTime);
	cutoffItem->setData(Qt::UserRole, cutoffVariant);

	auto& stopwatchUI = ui->StopwatchUI;

	stopwatchUI.cutoffTable->insertRow(0);

	stopwatchUI.cutoffTable->setItem(0, 1, cutoffItem);
	stopwatchUI.cutoffTable->setItem(0, 2, totalItem);

	cutoffTime = 0;

	int rowCount = stopwatchUI.cutoffTable->rowCount();

	stopwatchUI.cutoffTable->setItem(0, 0, new QTableWidgetItem("1"));

	if (rowCount <= 1)
		return;

	int fastestRow = 0;
	int slowestRow = 0;

	for (int row = 0; row < rowCount; row++)
	{
		auto currentItem = stopwatchUI.cutoffTable->item(row, 1);
		auto fastestItem = stopwatchUI.cutoffTable->item(fastestRow, 1);
		auto slowestItem = stopwatchUI.cutoffTable->item(slowestRow, 1);

		if (currentItem)
		{
			int current = currentItem->data(Qt::UserRole).toInt();
			int fastest = fastestItem->data(Qt::UserRole).toInt();
			int slowest = slowestItem->data(Qt::UserRole).toInt();

			if (current > slowest)
				slowestRow = row;

			if (current < fastest)
				fastestRow = row;
		}

		stopwatchUI.cutoffTable->setItem(row, 0, new QTableWidgetItem(tr("%1").arg(rowCount - row)));
	}

	auto spaces = QString(11, ' ');
	auto fastestItem = new QTableWidgetItem(tr("%1%2%3").arg(rowCount-fastestRow).arg(spaces).arg("The fastest"));
	auto slowestItem = new QTableWidgetItem(tr("%1%2%3").arg(rowCount-slowestRow).arg(spaces).arg("The slowest"));

	stopwatchUI.cutoffTable->setItem(fastestRow, 0, fastestItem);
	stopwatchUI.cutoffTable->setItem(slowestRow, 0, slowestItem);
}

MainWindow::~MainWindow()
{
	delete ui;

	delete overlayWidget;

	dbManager->close();

	delete dbManager;
}

void MainWindow::increaseMenu()
{
	auto& menuUI = ui->MenuUI;

	menuUI.centralWidget->setStyleSheet(R"(
		background-color: #202020; 
		border-top-right-radius: 4px;
		border-bottom-right-radius: 4px;
		border-top: 1px solid #434343;
		border-right: 1px solid #434343;
		border-bottom: 1px solid #434343;
	)");

	menuUI.alarmClockButton->setText("    Alarm clock");
	menuUI.timerButton->setText("    Timer");
	menuUI.stopwatchButton->setText("    Stopwatch");
	menuUI.worldClockButton->setText("    World clock");

	menuUI.centralWidget->setFixedWidth(280);

	menuExpanded = true;
}

void MainWindow::decreaseMenu()
{
	auto& menuUI = ui->MenuUI;
	
	menuUI.centralWidget->setStyleSheet("background-color: #202020; border: 0; border-radius: 0;");

	menuUI.alarmClockButton->setText("");
	menuUI.timerButton->setText("");
	menuUI.stopwatchButton->setText("");
	menuUI.worldClockButton->setText("");

	menuUI.centralWidget->setFixedWidth(48);
	
	menuExpanded = false;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	emit closed();
	QMainWindow::closeEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	ui->MenuUI.centralWidget->setFixedHeight(this->height());
	QMainWindow::resizeEvent(event);
}

void MainWindow::setSideMenuConnections()
{
	auto& menuUI = ui->MenuUI;

	connect(menuUI.menuButton, &QPushButton::clicked, [&] {
		if (menuExpanded)
		{
			decreaseMenu();
		}
		else
		{
			increaseMenu();
		}
	});

	connect(menuUI.alarmClockButton, &QPushButton::toggled, [&](bool checked) {
		if (checked)
			ui->AlarmClockUI.centralWidget->show();
		else
			ui->AlarmClockUI.centralWidget->hide();
		decreaseMenu();
	});

	connect(menuUI.alarmClockButton, &QPushButton::clicked, this, &MainWindow::decreaseMenu);

	connect(menuUI.timerButton, &QPushButton::toggled, [&](bool checked) {
		if (checked)
			ui->TimerUI.centralWidget->show();
		else
			ui->TimerUI.centralWidget->hide();
		decreaseMenu();
		});

	connect(menuUI.timerButton, &QPushButton::clicked, this, &MainWindow::decreaseMenu);

	connect(menuUI.stopwatchButton, &QPushButton::toggled, [&](bool checked) {
		if (checked)
			ui->StopwatchUI.centralWidget->show();
		else
			ui->StopwatchUI.centralWidget->hide();
		decreaseMenu();
		});

	connect(menuUI.stopwatchButton, &QPushButton::clicked, this, &MainWindow::decreaseMenu);

	connect(menuUI.worldClockButton, &QPushButton::toggled, [&](bool checked) {
		if (checked)
			ui->WorldClockUI.centralWidget->show();
		else
			ui->WorldClockUI.centralWidget->hide();
		decreaseMenu();
		});

	connect(menuUI.worldClockButton, &QPushButton::clicked, this, &MainWindow::decreaseMenu);
}

void MainWindow::setAlarmClockConnections()
{
	connect(this, &MainWindow::alarmClockAdded, dbManager, &DatabaseManager::insertAlarmData);
	connect(this, &MainWindow::alarmClockUpdated, dbManager, &DatabaseManager::updateAlarmData);
	connect(this, &MainWindow::alarmClockDeleted, dbManager, &DatabaseManager::deleteAlarmData);

	auto& alarmUI = ui->AlarmClockUI;

	connect(alarmUI.addButton, &QPushButton::clicked, this, &MainWindow::openAddAlarmWindow);

	connect(alarmUI.deleteButton, &QPushButton::clicked, [&] {
		alarmUI.deleteButton->hide();
		alarmUI.confirmButton->show();

		for (int i = 0; i < alarmUI.listLayout->count(); i++)
		{
			AlarmClockWidget* alarm = qobject_cast<AlarmClockWidget*>(alarmUI.listLayout->itemAt(i)->widget());
			alarm->deleteMode(true);
		}

	});

	connect(alarmUI.confirmButton, &QPushButton::clicked, [&] {
		alarmUI.confirmButton->hide();
		alarmUI.deleteButton->show();

		for (int i = 0; i < alarmUI.listLayout->count(); i++)
		{
			AlarmClockWidget* alarm = qobject_cast<AlarmClockWidget*>(alarmUI.listLayout->itemAt(i)->widget());
			alarm->deleteMode(false);
		}
	});

	auto updateTimer = [&]() {
		QTime currentTime = QTime::currentTime();

		for (int i = 0; i < alarmUI.listLayout->count(); i++)
		{
			AlarmClockWidget* alarm = qobject_cast<AlarmClockWidget*>(alarmUI.listLayout->itemAt(i)->widget());
			QTime remainingTime = QTime(0, 0).addSecs(currentTime.secsTo(alarm->getAlarmTime()) + 60);
			QString remainingTimeString = "in ";

			if (remainingTime.hour() == 0 && remainingTime.minute() == 0)
			{
				remainingTimeString += "1 day";
			}
			else if (remainingTime.hour() == 0)
			{
				if (remainingTime.minute() == 1)
					remainingTimeString += "1 minute";
				else
					remainingTimeString += QString("%1 minutes").arg(remainingTime.minute());
			}
			else if (remainingTime.minute() == 0)
			{
				if (remainingTime.hour() == 1)
					remainingTimeString += "1 hour";
				else
					remainingTimeString += QString("%1 hours").arg(remainingTime.hour());
			}
			else
			{
				remainingTimeString += QString("%1 h, %2 min.").arg(remainingTime.hour()).arg(remainingTime.minute());
			}

			alarm->setRemainingTime(remainingTimeString);
		}
	};

	updateTimer();

	connect(this->timer, &QTimer::timeout, this, updateTimer);
}

void MainWindow::setTimerConnections()
{
	connect(this, &MainWindow::timerAdded, dbManager, &DatabaseManager::insertTimerData);
	connect(this, &MainWindow::timerUpdated, dbManager, &DatabaseManager::updateTimerData);
	connect(this, &MainWindow::timerDeleted, dbManager, &DatabaseManager::deleteTimerData);

	auto& timerUI = ui->TimerUI;

	connect(timerUI.deleteButton, &QPushButton::clicked, [&] {
		timerUI.deleteButton->hide();
		timerUI.confirmButton->show();

		// Delete mode on
		for (int i = 0; i < timerUI.listLayout->count(); i++)
		{
			TimerWidget* timer = qobject_cast<TimerWidget*>(timerUI.listLayout->itemAt(i)->widget());
			timer->deleteMode(true);
		}

	});

	connect(timerUI.confirmButton, &QPushButton::clicked, [&] {
		timerUI.confirmButton->hide();
		timerUI.deleteButton->show();

		// Delete mode off
		for (int i = 0; i < timerUI.listLayout->count(); i++)
		{
			TimerWidget* timer = qobject_cast<TimerWidget*>(timerUI.listLayout->itemAt(i)->widget());
			timer->deleteMode(false);
		}
	});

	connect(timerUI.addButton, &QPushButton::clicked, this, &MainWindow::openAddTimerWindow);
}

void MainWindow::setStopwatchConnections()
{
	stopwatchTimer = new QTimer(this);
	stopwatchTimer->setInterval(10);
	connect(stopwatchTimer, &QTimer::timeout, this, &MainWindow::stopwatchUpdateTime);

	auto& stopwatchUI = ui->StopwatchUI;

	connect(stopwatchUI.startButton, &QPushButton::clicked, this, [&] {
		this->stopwatchTimer->start();
		stopwatchUI.startButton->hide();
		stopwatchUI.pauseButton->show();
		stopwatchUI.cutoffButton->setDisabled(false);
		stopwatchUI.cutoffButton->setInactiveIcon(false);
		stopwatchUI.label ->setStyleSheet("color: white");
		});

	connect(stopwatchUI.pauseButton, &QPushButton::clicked, this, [&] {
		this->stopwatchTimer->stop();
		stopwatchUI.pauseButton->hide();
		stopwatchUI.startButton->show();
		stopwatchUI.cutoffButton->setDisabled(true);
		stopwatchUI.cutoffButton->setInactiveIcon(true);
		stopwatchUI.label->setStyleSheet("color: #CECECE");
		});

	connect(stopwatchUI.resetButton, &QPushButton::clicked, this, [&] {
		this->stopwatchTimer->stop();
		stopwatchUI.pauseButton->hide();
		stopwatchUI.startButton->show();
		stopwatchUI.cutoffButton->setDisabled(true);
		stopwatchUI.cutoffButton->setInactiveIcon(true);
		stopwatchUI.label->setStyleSheet("color: #CECECE");

		stopwatchTime = 0;
		cutoffTime = 0;

		stopwatchUI.cutoffTable->setRowCount(0);

		stopwatchUpdateTime();
		});

	connect(stopwatchUI.cutoffButton, &QPushButton::clicked, this, &MainWindow::cutoffTableCalculations);

	connect(stopwatchUI.cutoffTable->model(), &QAbstractItemModel::rowsInserted, [&] {
		stopwatchUI.cutoffTable->show();
		stopwatchUI.cutoffTable->verticalScrollBar()->setFixedHeight(stopwatchUI.cutoffTable->height());
		});

	connect(stopwatchUI.cutoffTable->model(), &QAbstractItemModel::rowsRemoved, [&] {
		if (stopwatchUI.cutoffTable->rowCount() < 1)
			stopwatchUI.cutoffTable->hide();
		});
}

void MainWindow::setWorldClockConnections()
{
	connect(this, &MainWindow::clockAdded, dbManager, &DatabaseManager::insertClockData);
	connect(this, &MainWindow::clockDeleted, dbManager, &DatabaseManager::deleteClockData);

	auto& worldClockUI = ui->WorldClockUI;

	connect(worldClockUI.addButton, &QPushButton::clicked, this, &MainWindow::openAddClockWindow);

	connect(worldClockUI.deleteButton, &QPushButton::clicked, [&] {
		worldClockUI.deleteButton->hide();
		worldClockUI.confirmButton->show();

		for (int i = 1; i < worldClockUI.listLayout->count(); i++)
		{
			ClockWidget* clock= qobject_cast<ClockWidget*>(worldClockUI.listLayout->itemAt(i)->widget());
			clock->deleteMode(true);
		}
	});

	connect(worldClockUI.confirmButton, &QPushButton::clicked, [&] {
		worldClockUI.confirmButton->hide();
		worldClockUI.deleteButton->show();

		for (int i = 1; i < worldClockUI.listLayout->count(); i++)
		{
			ClockWidget* clock = qobject_cast<ClockWidget*>(worldClockUI.listLayout->itemAt(i)->widget());
			clock->deleteMode(false);
		}
	});

	auto updateWorldClocksTime = [&](){
		for (int i = 0; i < worldClockUI.listLayout->count(); i++)
		{
			ClockWidget* clock = qobject_cast<ClockWidget*>(worldClockUI.listLayout->itemAt(i)->widget());
			clock->updateUI();
		}
	};

	QObject::connect(this->timer, &QTimer::timeout, this, updateWorldClocksTime);
}

void MainWindow::checkAlarm()
{
	QTime currentTime = QTime::currentTime();

	auto& alarmUI = ui->AlarmClockUI;

	for (int i = 0; i < alarmUI.listLayout->count(); ++i)
	{
		AlarmClockWidget* alarm = dynamic_cast<AlarmClockWidget*>(alarmUI.listLayout->itemAt(i)->widget());
		if (alarm)
		{
			QTime alarmTime = alarm->getAlarmTime();

			if (currentTime >= alarmTime &&
				currentTime < alarmTime.addSecs(2) &&
				alarm->isActive() &&
				!alarm->isNotifficationOpen())
			{
				// Alarm went off
				auto notificationWindow = new AlarmNotificationWindow(nullptr, alarm);

				connect(notificationWindow, &AlarmNotificationWindow::alarmSnoozed, this->dbManager, &DatabaseManager::updateAlarmData);

				connect(this, &MainWindow::closed, notificationWindow, &QDialog::close);

				QRect scr = QGuiApplication::primaryScreen()->geometry();

				notificationWindow->show();
				notificationWindow->activateWindow();
				notificationWindow->raise();


				notificationWindow->move((scr.right() - notificationWindow->frameSize().width()), (scr.bottom() - notificationWindow->frameSize().height()));
			}
		}
	}
}

void MainWindow::openAddAlarmWindow()
{
	emit childWindowShowed();

	AddAlarmWindow* addAlarmWindow = new AddAlarmWindow(this);
	addAlarmWindow->setModal(true);

	addAlarmWindow->setFocus();

	connect(addAlarmWindow, &AddAlarmWindow::setAlarm, this, [&](const int& id, const QString& name, const QTime& time) {
		AlarmClockWidget* alarm = setAlarm(id, name, time);
		alarm->setActive(true);
		emit alarmClockAdded(id, name, time);
	});

	connect(addAlarmWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});

	addAlarmWindow->exec();
}

void MainWindow::openAddTimerWindow()
{
	emit childWindowShowed();

	auto addTimerWindow = new AddTimerWindow(this);
	addTimerWindow->setModal(true);

	addTimerWindow->setFocus();

	connect(addTimerWindow, &AddTimerWindow::setTimer, this, [&](const int& id, const QString& name, const QTime& time) {
		TimerWidget* timer = setTimer(id, name, time);
		emit timerAdded(id, name, time);
	});

	connect(addTimerWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
		});

	addTimerWindow->exec();
}

void MainWindow::openEditAlarmWindow(AlarmClockWidget* alarm)
{
	emit childWindowShowed();

	EditAlarmWindow* editAlarmWindow = new EditAlarmWindow(this, alarm);
	editAlarmWindow->setModal(true);

	editAlarmWindow->setFocus();

	connect(editAlarmWindow, &EditAlarmWindow::updateAlarm, this, &MainWindow::updateAlarm);
	connect(editAlarmWindow, &EditAlarmWindow::deleteAlarm, this, &MainWindow::deleteAlarm);

	connect(editAlarmWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});

	editAlarmWindow->exec();
}

void MainWindow::openEditTimerWindow(TimerWidget* timer)
{
	emit childWindowShowed();

	auto editTimerWindow = new EditTimerWindow(this, timer);
	editTimerWindow->setModal(true);

	editTimerWindow->setFocus();

	connect(editTimerWindow, &EditTimerWindow::updateTimer, this, &MainWindow::updateTimer);
	connect(editTimerWindow, &EditTimerWindow::deleteTimer, this, &MainWindow::deleteTimer);

	connect(editTimerWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});

	editTimerWindow->exec();
}

AlarmClockWidget* MainWindow::setAlarm(const int& id, const QString& name, const QTime& time)
{
	AlarmClockWidget* alarm = new AlarmClockWidget(this, id, time, name);
	ui->AlarmClockUI.listLayout->addWidget(alarm);

	QObject::connect(alarm, &AlarmClockWidget::clicked, this, &MainWindow::openEditAlarmWindow);
	QObject::connect(alarm, &AlarmClockWidget::deleteButtonClicked, this, &MainWindow::deleteAlarm);

	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);

	return alarm;
}

TimerWidget* MainWindow::setTimer(const int& id, const QString& name, const QTime& time)
{
	auto timer = new TimerWidget(this, id, time, name);
	ui->TimerUI.listLayout->addWidget(timer);

	QObject::connect(timer, &TimerWidget::clicked, this, &MainWindow::openEditTimerWindow);
	QObject::connect(timer, &TimerWidget::deleteButtonClicked, this, &MainWindow::deleteTimer);

	QObject::connect(timer, &TimerWidget::expired, this, [&](TimerWidget* timer) {
		MainWindow::openTimerNotificationWindow(timer);
		timer->showPlayButton();
	});

	return timer;
}

ClockWidget* MainWindow::addClock(const int& id, const QByteArray& timeZoneId)
{
	auto clock = new ClockWidget(this, id, timeZoneId);
	ui->WorldClockUI.listLayout->addWidget(clock);

	QObject::connect(clock, &ClockWidget::deleteButtonClicked, this, &MainWindow::deleteClock);

	return clock;
}

void MainWindow::openTimerNotificationWindow(TimerWidget* timer)
{
	auto notificationWindow = new TimerNotificationWindow(nullptr, timer);

	connect(this, &MainWindow::closed, notificationWindow, &QDialog::close);

	QRect scr = QGuiApplication::primaryScreen()->geometry();

	notificationWindow->show();
	notificationWindow->activateWindow();
	notificationWindow->raise();

	notificationWindow->move((scr.right() - notificationWindow->frameSize().width()), (scr.bottom() - notificationWindow->frameSize().height()));
}

void MainWindow::openAddClockWindow()
{
	emit childWindowShowed();

	AddClockWindow* addClockWindow = new AddClockWindow(this);
	addClockWindow->setModal(true);

	addClockWindow->setFocus();

	connect(addClockWindow, &AddClockWindow::setClock, this, [&](const int& id, const QByteArray& timeZoneId) {
		ClockWidget* clock = addClock(id, timeZoneId);
		emit clockAdded(id, timeZoneId);
	});

	connect(addClockWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});

	addClockWindow->exec();
}

void MainWindow::updateAlarm(AlarmClockWidget* alarm, const QString& name, const QTime& time)
{
	alarm->setName(name);
	alarm->setAlarmTime(time);
	alarm->updateUI();

	emit alarmClockUpdated(alarm->getId(), name, time);
}

void MainWindow::updateTimer(TimerWidget* timer, const QString& name, const QTime& time)
{
	timer->setName(name);
	timer->setTime(time);
	timer->updateUI();

	emit timerUpdated(timer->getId(), name, time);
}

void MainWindow::deleteAlarm(AlarmClockWidget* alarm)
{
	emit alarmClockDeleted(alarm->getId());
	alarm->deleteLater();
}

void MainWindow::deleteTimer(TimerWidget* timer)
{
	emit timerDeleted(timer->getId());
	timer->deleteLater();
}

void MainWindow::deleteClock(ClockWidget* clock)
{
	emit clockDeleted(clock->getId());
	clock->deleteLater();
}
