#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), ui(new Ui::MainWindowClass), setAlarmWindow(nullptr)
{
	ui->setupMainWindowUI(this);

	resize(900, 550);

	setAlarmWindow = new SetAlarmWindow(this);

	setAlarmWindow->setModal(true);

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

	connect(ui->mainWindowSetAlarmButton, &QPushButton::clicked, this, &MainWindow::openSetAlarmWindow);

	connect(setAlarmWindow, &SetAlarmWindow::setAlarm, this, [&](const int& id, const QString& name, const QTime& time) {
		setAlarm(id, name, time);
		emit alarmClockAdded(id, name, time);
	});
	
	connect(this, &MainWindow::childWindowShowed, [&]() {
		overlayWidget->show();
	});

	connect(setAlarmWindow, &QDialog::finished, [&]() {
		overlayWidget->hide();
	});
}

MainWindow::~MainWindow()
{
	delete ui;

	delete setAlarmWindow;

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

void MainWindow::openSetAlarmWindow()
{
	emit childWindowShowed();

	setAlarmWindow->setDefaultValues();

	setAlarmWindow->setDefaultFocus();

	setAlarmWindow->exec();
}

void MainWindow::setAlarm(const int& id, const QString& name, const QTime& time)
{
	AlarmClockWidget* alarm = new AlarmClockWidget(this, id, time, name);
	
	QListWidgetItem* item = new QListWidgetItem(ui->alarmsListWidget);
	item->setSizeHint(QSize(733, 226));

	ui->alarmsListWidget->setItemWidget(item, alarm);
	
	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);
}