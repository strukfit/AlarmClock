#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), 
	ui(new Ui::MainWindowClass)
{
	ui->setupMainWindowUI(this);

	resize(900, 550);

	overlayWidget = new QWidget(this);
	overlayWidget->setGeometry(geometry());
	overlayWidget->setStyleSheet("background-color: rgba(0, 0, 0, 0.75);");
	overlayWidget->hide();

	dbManager = new DatabaseManager(this);

	connect(dbManager, &DatabaseManager::dataReceived, this, &MainWindow::setAlarm);

	dbManager->open();

	dbManager->tableInit();

	dbManager->selectAll();

	AlarmClockWidget::count = ui->alarmsListWidget->count();

	connect(this, &MainWindow::alarmClockAdded, dbManager, &DatabaseManager::insertData);
	connect(this, &MainWindow::alarmClockUpdated, dbManager, &DatabaseManager::updateData);
	connect(this, &MainWindow::alarmClockDeleted, dbManager, &DatabaseManager::deleteData);

	connect(ui->addAlarmButton, &QPushButton::clicked, this, &MainWindow::openAddAlarmWindow);


	connect(this, &MainWindow::childWindowShowed, [&]() {
		//overlayWidget->setGeometry(geometry());
		overlayWidget->show();
	});

	connect(ui->alarmsListWidget, &QListWidget::itemClicked, [&](QListWidgetItem* item){
		int listId = ui->alarmsListWidget->row(item);

		AlarmClockWidget* selectedAlarm = qobject_cast<AlarmClockWidget*>(ui->alarmsListWidget->itemWidget(item));

		openEditAlarmWindow(listId, selectedAlarm->getName(), selectedAlarm->getAlarmTime());
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

	for (int i = 0; i < ui->alarmsListWidget->count(); ++i)
	{
		AlarmClockWidget* alarmClock = dynamic_cast<AlarmClockWidget*>(ui->alarmsListWidget->itemWidget(ui->alarmsListWidget->item(i)));
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
		setAlarm(id, name, time);
		emit alarmClockAdded(id, name, time);
	});

	connect(addAlarmWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});

	addAlarmWindow->exec();

	delete addAlarmWindow;
}

void MainWindow::openEditAlarmWindow(const int& listId, const QString& name, const QTime& time)
{
	emit childWindowShowed();

	EditAlarmWindow* editAlarmWindow = new EditAlarmWindow(this, listId);
	editAlarmWindow->setModal(true);

	editAlarmWindow->setValues(name, time);

	editAlarmWindow->setFocus();

	connect(editAlarmWindow, &EditAlarmWindow::updateAlarm, this, &MainWindow::updateAlarm);
	connect(editAlarmWindow, &EditAlarmWindow::deleteAlarm, this, &MainWindow::deleteAlarm);

	connect(editAlarmWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});

	editAlarmWindow->exec();

	delete editAlarmWindow;
}

void MainWindow::setAlarm(const int& id, const QString& name, const QTime& time)
{
	AlarmClockWidget* alarm = new AlarmClockWidget(this, id, time, name);
	
	QListWidgetItem* item = new QListWidgetItem(ui->alarmsListWidget);
	item->setSizeHint(QSize(733, 226));

	ui->alarmsListWidget->setItemWidget(item, alarm);
	
	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);
}

void MainWindow::updateAlarm(const int& listId, const QString& name, const QTime& time)
{
	QListWidgetItem* item = ui->alarmsListWidget->item(listId);

	if (item)
	{
		AlarmClockWidget* selectedAlarm = qobject_cast<AlarmClockWidget*>(ui->alarmsListWidget->itemWidget(item));

		if (selectedAlarm)
		{
			selectedAlarm->setName(name);
			selectedAlarm->setAlarmTime(time);

			ui->alarmsListWidget->setItemWidget(item, selectedAlarm);
			//QMessageBox::information(this, "", "name: " + selectedAlarm->getName() + " time " + selectedAlarm->getAlarmTime().toString("hh:mm"));
			//ui->alarmsListWidget->update();

			selectedAlarm->updateUI();

			emit alarmClockUpdated(selectedAlarm->getId(), name, time);
		}
	}
}

void MainWindow::deleteAlarm(const int& listId)
{
	QListWidgetItem* item = ui->alarmsListWidget->item(listId);

	if (item)
	{
		AlarmClockWidget* selectedAlarm = qobject_cast<AlarmClockWidget*>(ui->alarmsListWidget->itemWidget(item));

		if (selectedAlarm)
		{

			ui->alarmsListWidget->removeItemWidget(item);

			emit alarmClockDeleted(selectedAlarm->getId());
		}

		delete selectedAlarm;
	}

	delete item;
}
