#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent), ui(new Ui::MainWindowClass)
{
	ui->setupMainWindowUI(this);

	resize(900, 550);

	AlarmClockWidget* alarm1 = new AlarmClockWidget(this, 1, QTime(1, 1), "alarm" + QString::number(AlarmClockWidget::count + 1));

	AlarmClockWidget* alarm2 = new AlarmClockWidget(this, 2, QTime(2, 2), "alarm" + QString::number(AlarmClockWidget::count + 1));

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
	SetAlarmWindow* setAlarmWindow = new SetAlarmWindow(this);
	setAlarmWindow->setModal(true);

	connect(setAlarmWindow, &SetAlarmWindow::setAlarm, this, &MainWindow::setAlarm);

	setAlarmWindow->exec();
}

void MainWindow::setAlarm(const QTime& time)
{
	AlarmClockWidget* alarm = new AlarmClockWidget(this, AlarmClockWidget::count + 1, time, "alarm" + QString::number(AlarmClockWidget::count + 1));
	
	QListWidgetItem* item = new QListWidgetItem(ui->alarmsListWidget);
	//item->setSizeHint(QSize(100, 100));
	item->setSizeHint(QSize(733, 226));

	ui->alarmsListWidget->setItemWidget(item, alarm);

	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);
}