#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), ui(new Ui::MainWindowClass), setAlarmWindow(nullptr)
{
	ui->setupMainWindowUI(this);

	resize(900, 550);

	AlarmClockWidget* alarm1 = new AlarmClockWidget(this, 1, QTime(1, 1), "aboba1");

	AlarmClockWidget* alarm2 = new AlarmClockWidget(this, 2, QTime(2, 2), "aboba2");

	QListWidgetItem* item1 = new QListWidgetItem(ui->alarmsListWidget);
	item1->setSizeHint(QSize(733, 226));

	QListWidgetItem* item2 = new QListWidgetItem(ui->alarmsListWidget);
	item2->setSizeHint(QSize(733, 226));

	ui->alarmsListWidget->setItemWidget(item1, alarm1);
	ui->alarmsListWidget->setItemWidget(item2, alarm2);

	connect(ui->mainWindowSetAlarmButton, &QPushButton::pressed, this, &MainWindow::openSetAlarmWindow);
}

MainWindow::~MainWindow()
{
	delete ui;

	delete setAlarmWindow;
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
	setAlarmWindow = new SetAlarmWindow(this);
	setAlarmWindow->setModal(true);

	connect(setAlarmWindow, &SetAlarmWindow::setAlarm, this, &MainWindow::setAlarm);

	setAlarmWindow->exec();
}

void MainWindow::setAlarm(const QTime& time, const QString name)
{
	AlarmClockWidget* alarm = new AlarmClockWidget(this, 1, time, name);
	
	QListWidgetItem* item = new QListWidgetItem(ui->alarmsListWidget);
	//item->setSizeHint(QSize(100, 100));
	item->setSizeHint(QSize(733, 226));

	ui->alarmsListWidget->setItemWidget(item, alarm);

	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);
}