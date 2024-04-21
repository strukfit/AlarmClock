#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), 
	ui(new Ui::MainWindowClass)
{
	ui->setupUI(this);

	overlayWidget = new QWidget(this);
	overlayWidget->setGeometry(geometry());
	overlayWidget->setStyleSheet("background-color: rgba(0, 0, 0, 0.75);");
	overlayWidget->hide();

	dbManager = new DatabaseManager(this);

	connect(dbManager, &DatabaseManager::dataReceived, this, &MainWindow::setAlarm);

	dbManager->open();

	dbManager->tableInit();

	dbManager->selectAll();

	AlarmClockWidget::lastId = dbManager->getLastId();

	connect(this, &MainWindow::alarmClockAdded, dbManager, &DatabaseManager::insertData);
	connect(this, &MainWindow::alarmClockUpdated, dbManager, &DatabaseManager::updateData);
	connect(this, &MainWindow::alarmClockDeleted, dbManager, &DatabaseManager::deleteData);

	connect(ui->addAlarmButton, &QPushButton::clicked, this, &MainWindow::openAddAlarmWindow);

	connect(this, &MainWindow::childWindowShowed, [&]() {
		overlayWidget->resize(size());
		overlayWidget->show();
	});

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

	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, updateTimer);
	timer->start(1000);

	AlarmClockWidget* alarm = qobject_cast<AlarmClockWidget*>(ui->alarmsListLayout->itemAt(0)->widget());

	notificationWindow = new AlarmNotificationWindow(this, alarm);
	notificationWindow->show();
}

MainWindow::~MainWindow()
{
	delete ui;

	delete overlayWidget;

	dbManager->close();

	delete dbManager;
}

void MainWindow::checkAlarm()
{
	QTime currentTime = QTime::currentTime();

	for (int i = 0; i < ui->alarmsListLayout->count(); ++i)
	{
		AlarmClockWidget* alarmClock = dynamic_cast<AlarmClockWidget*>(ui->alarmsListLayout->itemAt(i)->widget());
		if (alarmClock)
		{
			QTime alarmTime = alarmClock->getAlarmTime();

			if (currentTime >= alarmTime &&
				currentTime < alarmTime.addSecs(5) &&
				alarmClock->isActive())
			{
				//alarmClock->setActive(false);
				// Alarm went off
			}
		}
	}

	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);
}

void MainWindow::openAddAlarmWindow()
{
	emit childWindowShowed();

	AddAlarmWindow* addAlarmWindow = new AddAlarmWindow(this);
	addAlarmWindow->setModal(true);

	//addAlarmWindow->setDefaultValues();

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

	delete addAlarmWindow;
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

	delete editAlarmWindow;
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

void MainWindow::updateAlarm(AlarmClockWidget* alarm, const QString& name, const QTime& time)
{
	alarm->setName(name);
	alarm->setAlarmTime(time);
	alarm->updateUI();

	emit alarmClockUpdated(alarm->getId(), name, time);
}

void MainWindow::deleteAlarm(AlarmClockWidget* alarm)
{
	emit alarmClockDeleted(alarm->getId());

	/*QSettings settings(settingsFile, QSettings::IniFormat);
	int defaultNameCounter = settings.value("defaultNameCounter", 0).toInt();
	settings.setValue("defaultNameCounter", --defaultNameCounter);*/

	alarm->deleteLater();
}
