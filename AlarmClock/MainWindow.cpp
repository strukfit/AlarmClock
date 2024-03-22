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
	overlayWidget->setStyleSheet("background-color: rgba(0, 0, 0, 0.5);");
	overlayWidget->hide();

	AlarmClockWidget* alarm1 = new AlarmClockWidget(this, 1, QTime(1, 1), "aboba1");

	AlarmClockWidget* alarm2 = new AlarmClockWidget(this, 2, QTime(2, 2), "aboba2");

	QListWidgetItem* item1 = new QListWidgetItem(ui->alarmsListWidget);
	item1->setSizeHint(QSize(733, 226));

	QListWidgetItem* item2 = new QListWidgetItem(ui->alarmsListWidget);
	item2->setSizeHint(QSize(733, 226));

	ui->alarmsListWidget->setItemWidget(item1, alarm1);
	ui->alarmsListWidget->setItemWidget(item2, alarm2);

	connect(ui->mainWindowSetAlarmButton, &QPushButton::clicked, this, &MainWindow::openSetAlarmWindow);

	connect(setAlarmWindow, &SetAlarmWindow::setAlarm, this, &MainWindow::setAlarm);
	
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

void MainWindow::setAlarm(const QTime& time, const QString name)
{
	AlarmClockWidget* alarm = new AlarmClockWidget(this, 1, time, name);
	
	QListWidgetItem* item = new QListWidgetItem(ui->alarmsListWidget);
	item->setSizeHint(QSize(733, 226));

	ui->alarmsListWidget->setItemWidget(item, alarm);

	QTimer::singleShot(1000, this, &MainWindow::checkAlarm);
}