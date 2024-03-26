#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), 
	ui(new Ui::MainWindowClass)
{
	ui->setupMainWindowUI(this);

	resize(900, 550);

	addAlarmWindow = new AddAlarmWindow(this);
	addAlarmWindow->setModal(true);

	editAlarmWindow = new EditAlarmWindow(this);
	editAlarmWindow->setModal(true);

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

	connect(ui->addAlarmButton, &QPushButton::clicked, this, &MainWindow::openAddAlarmWindow);

	connect(addAlarmWindow, &AddAlarmWindow::setAlarm, this, [&](const int& id, const QString& name, const QTime& time) {
		setAlarm(id, name, time);
		emit alarmClockAdded(id, name, time);
	});
	
	connect(this, &MainWindow::childWindowShowed, [&]() {
		overlayWidget->show();
	});

	connect(addAlarmWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});

	connect(editAlarmWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});

	connect(ui->alarmsListWidget, &QListWidget::itemClicked, [&](QListWidgetItem* item){
		//int listIndex = ui->alarmsListWidget->row(item);
		//AlarmClockWidget* a = qobject_cast<AlarmClockWidget*>(ui->alarmsListWidget->itemWidget(item));
		//QMessageBox::information(this, "", "index: " + QString::number(listIndex) + "id: " + QString::number(a->getId()));

		AlarmClockWidget* a = qobject_cast<AlarmClockWidget*>(ui->alarmsListWidget->itemWidget(item));

		openEditAlarmWindow(a->getName(), a->getAlarmTime());
	});
}

MainWindow::~MainWindow()
{
	delete ui;

	delete addAlarmWindow;

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

	addAlarmWindow->setDefaultValues();

	addAlarmWindow->setFocus();

	addAlarmWindow->exec();
}

void MainWindow::openEditAlarmWindow(const QString& name, const QTime& time)
{
	emit childWindowShowed();

	editAlarmWindow->setValues(name, time);

	editAlarmWindow->setFocus();

	editAlarmWindow->exec();
}

void MainWindow::setAlarm(const int& id, const QString& name, const QTime& time)
{
	AlarmClockWidget* alarm = new AlarmClockWidget(this, id, time, name);
	
	QListWidgetItem* item = new QListWidgetItem(ui->alarmsListWidget);
	item->setSizeHint(QSize(733, 226));

	ui->alarmsListWidget->setItemWidget(item, alarm);
	
	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);
}