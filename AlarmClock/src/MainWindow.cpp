#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), 
	ui(new Ui::MainWindowClass)
{
	ui->setupMainWindowUI(this);

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
				alarmClock->setActive(false);
				QMessageBox::information(nullptr, "Alarm", "The alarm went off!");
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

	addAlarmWindow->setDefaultValues();

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

	QSettings settings(settingsFile, QSettings::IniFormat);
	int defaultNameCounter = settings.value("defaultNameCounter", 0).toInt();

	if (alarm->getName() == (defaultName + " (" + QString::number(defaultNameCounter) + ")"))
	{
		defaultNameCounter--;

		settings.setValue("defaultNameCounter", defaultNameCounter);
	}

	alarm->deleteLater();
	
	AlarmClockWidget::lastId--;
}
