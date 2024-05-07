#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), 
	ui(new Ui::MainWindowClass),
	menuExpanded(false)
{
	ui->setupUI(this);

	overlayWidget = new QWidget(this);
	overlayWidget->setGeometry(geometry());
	overlayWidget->setStyleSheet("background-color: rgba(0, 0, 0, 0.75);");
	overlayWidget->hide();

	dbManager = new DatabaseManager(this);

	connect(dbManager, &DatabaseManager::alarmDataReceived, this, &MainWindow::setAlarm);
	connect(dbManager, &DatabaseManager::timerDataReceived, this, &MainWindow::setTimer);

	dbManager->open();

	dbManager->tableInit();

	dbManager->selectAllAlarms();
	dbManager->selectAllTimers();

	AlarmClockWidget::lastId = dbManager->getLastAlarmId();
	TimerWidget::lastId = dbManager->getLastTimerId();
	
	setSideMenuConnections();

	connect(this, &MainWindow::childWindowShowed, [&] {
		overlayWidget->resize(size());
		overlayWidget->show();
	});

	timer = new QTimer(this);

	setAlarmClockConnections();
	connect(timer, &QTimer::timeout, this, &MainWindow::checkAlarm);
	setTimerConnections();
	timer->start(1000);	
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
	ui->functionSelectorWidget->setStyleSheet(R"(
		background-color: #202020; 
		border-top-right-radius: 4px;
		border-bottom-right-radius: 4px;
		border-top: 1px solid #434343;
		border-right: 1px solid #434343;
		border-bottom: 1px solid #434343;
	)");

	ui->alarmClockButton->setText("    Alarm clock");
	ui->timerButton->setText("    Timer");
	ui->stopwatchButton->setText("    Stopwatch");
	ui->worldClockButton->setText("    World clock");

	ui->functionSelectorWidget->setFixedWidth(280);

	menuExpanded = true;
}

void MainWindow::decreaseMenu()
{
	ui->functionSelectorWidget->setStyleSheet("background-color: #202020; border: 0; border-radius: 0;");

	ui->alarmClockButton->setText("");
	ui->timerButton->setText("");
	ui->stopwatchButton->setText("");
	ui->worldClockButton->setText("");

	ui->functionSelectorWidget->setFixedWidth(48);
	
	menuExpanded = false;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	emit closed();
	QMainWindow::closeEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	ui->functionSelectorWidget->setFixedHeight(this->height());
	QMainWindow::resizeEvent(event);
}

void MainWindow::setSideMenuConnections()
{
	connect(ui->menuButton, &QPushButton::clicked, [&] {
		if (menuExpanded)
		{
			decreaseMenu();
		}
		else
		{
			increaseMenu();
		}
		});

	connect(ui->alarmClockButton, &QPushButton::toggled, [&](bool checked) {
		if (checked)
			ui->alarmsWidget->show();
		else
			ui->alarmsWidget->hide();
		decreaseMenu();
		});

	connect(ui->alarmClockButton, &QPushButton::clicked, this, &MainWindow::decreaseMenu);

	connect(ui->timerButton, &QPushButton::toggled, [&](bool checked) {
		if (checked)
			ui->timerWidget->show();
		else
			ui->timerWidget->hide();
		decreaseMenu();
		});

	connect(ui->timerButton, &QPushButton::clicked, this, &MainWindow::decreaseMenu);

	connect(ui->stopwatchButton, &QPushButton::toggled, [&](bool checked) {
		if (checked)
			ui->stopwatchWidget->show();
		else
			ui->stopwatchWidget->hide();
		decreaseMenu();
		});

	connect(ui->stopwatchButton, &QPushButton::clicked, this, &MainWindow::decreaseMenu);

	connect(ui->worldClockButton, &QPushButton::toggled, [&](bool checked) {
		if (checked)
			ui->worldClockWidget->show();
		else
			ui->worldClockWidget->hide();
		decreaseMenu();
		});

	connect(ui->worldClockButton, &QPushButton::clicked, this, &MainWindow::decreaseMenu);
}

void MainWindow::setAlarmClockConnections()
{
	connect(this, &MainWindow::alarmClockAdded, dbManager, &DatabaseManager::insertAlarmData);
	connect(this, &MainWindow::alarmClockUpdated, dbManager, &DatabaseManager::updateAlarmData);
	connect(this, &MainWindow::alarmClockDeleted, dbManager, &DatabaseManager::deleteAlarmData);

	connect(ui->addAlarmButton, &QPushButton::clicked, this, &MainWindow::openAddAlarmWindow);

	connect(ui->deleteAlarmsButton, &QPushButton::clicked, [&] {
		ui->deleteAlarmsButton->hide();
		ui->confirmButton->show();

		for (int i = 0; i < ui->alarmsListLayout->count(); i++)
		{
			AlarmClockWidget* alarm = qobject_cast<AlarmClockWidget*>(ui->alarmsListLayout->itemAt(i)->widget());
			alarm->deleteMode(true);
		}

	});

	connect(ui->confirmButton, &QPushButton::clicked, [&] {
		ui->confirmButton->hide();
		ui->deleteAlarmsButton->show();

		for (int i = 0; i < ui->alarmsListLayout->count(); i++)
		{
			AlarmClockWidget* alarm = qobject_cast<AlarmClockWidget*>(ui->alarmsListLayout->itemAt(i)->widget());
			alarm->deleteMode(false);
		}
	});

	auto updateTimer = [&]() {
		QTime currentTime = QTime::currentTime();

		for (int i = 0; i < ui->alarmsListLayout->count(); i++)
		{
			AlarmClockWidget* alarm = qobject_cast<AlarmClockWidget*>(ui->alarmsListLayout->itemAt(i)->widget());
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
	//connect(ui->timerAddButton, &QPushButton::clicked, this, );

	connect(this, &MainWindow::timerAdded, dbManager, &DatabaseManager::insertTimerData);
	connect(this, &MainWindow::timerUpdated, dbManager, &DatabaseManager::updateTimerData);
	connect(this, &MainWindow::timerDeleted, dbManager, &DatabaseManager::deleteTimerData);

	connect(ui->deleteTimerButton, &QPushButton::clicked, [&] {
		ui->deleteTimerButton->hide();
		ui->timerConfirmButton->show();

		// Delete mode on
		for (int i = 0; i < ui->timerListLayout->count(); i++)
		{
			TimerWidget* timer = qobject_cast<TimerWidget*>(ui->timerListLayout->itemAt(i)->widget());
			timer->deleteMode(true);
		}

	});

	connect(ui->timerConfirmButton, &QPushButton::clicked, [&] {
		ui->timerConfirmButton->hide();
		ui->deleteTimerButton->show();

		// Delete mode off
		for (int i = 0; i < ui->timerListLayout->count(); i++)
		{
			TimerWidget* timer = qobject_cast<TimerWidget*>(ui->timerListLayout->itemAt(i)->widget());
			timer->deleteMode(false);
		}
	});

	connect(ui->timerAddButton, &QPushButton::clicked, this, &MainWindow::openAddTimerWindow);
}

void MainWindow::checkAlarm()
{
	QTime currentTime = QTime::currentTime();

	for (int i = 0; i < ui->alarmsListLayout->count(); ++i)
	{
		AlarmClockWidget* alarm = dynamic_cast<AlarmClockWidget*>(ui->alarmsListLayout->itemAt(i)->widget());
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
	ui->alarmsListLayout->addWidget(alarm);

	QObject::connect(alarm, &AlarmClockWidget::clicked, this, &MainWindow::openEditAlarmWindow);
	QObject::connect(alarm, &AlarmClockWidget::deleteButtonClicked, this, &MainWindow::deleteAlarm);

	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);

	return alarm;
}

TimerWidget* MainWindow::setTimer(const int& id, const QString& name, const QTime& time)
{
	auto timer = new TimerWidget(this, id, time, name);
	ui->timerListLayout->addWidget(timer);

	QObject::connect(timer, &TimerWidget::clicked, this, &MainWindow::openEditTimerWindow);
	QObject::connect(timer, &TimerWidget::deleteButtonClicked, this, &MainWindow::deleteTimer);

	QObject::connect(timer, &TimerWidget::expired, this, [&](TimerWidget* timer) {
		MainWindow::openTimerNotificationWindow(timer);
		timer->showPlayButton();
	});

	//QTimer::singleShot(1000, this, &MainWindow::checkAlarm);

	return timer;
}

void MainWindow::openTimerNotificationWindow(TimerWidget* timer)
{
	auto notificationWindow = new TimerNotificationWindow(this, timer);

	QRect scr = QGuiApplication::primaryScreen()->geometry();

	notificationWindow->show();
	notificationWindow->activateWindow();
	notificationWindow->raise();

	notificationWindow->move((scr.right() - notificationWindow->frameSize().width()), (scr.bottom() - notificationWindow->frameSize().height()));
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

	/*QSettings settings(settingsFile, QSettings::IniFormat);
	int defaultNameCounter = settings.value("defaultNameCounter", 0).toInt();
	settings.setValue("defaultNameCounter", --defaultNameCounter);*/

	alarm->deleteLater();
}

void MainWindow::deleteTimer(TimerWidget* timer)
{
	emit timerDeleted(timer->getId());

	timer->deleteLater();
}
