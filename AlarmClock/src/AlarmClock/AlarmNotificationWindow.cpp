#include "AlarmClock/AlarmNotificationWindow.h"

AlarmNotificationWindow::AlarmNotificationWindow(QMainWindow* parent, AlarmClockWidget* alarm) :
	QDialog(parent),
	ui(new Ui::AlarmNotificationWindowClass),
	alarm(alarm)
{
	ui->setupUI(this);

	ui->name->setText(alarm->getName());
	ui->time->setText(alarm->getAlarmTime().toString("hh:mm"));

	ui->snoozeComboBox->addItem("5 minutes", 300);
	ui->snoozeComboBox->addItem("10 minutes", 600);
	ui->snoozeComboBox->addItem("20 minutes", 1200);
	ui->snoozeComboBox->addItem("30 minutes", 1800);
	ui->snoozeComboBox->addItem("1 hour", 3600);

	ui->snoozeComboBox->setCurrentIndex(1);

	connect(ui->snoozeButton, &QPushButton::clicked, this, [&] {
		QMessageBox::information(this, "", (this->alarm->getAlarmTime().addSecs(ui->snoozeComboBox->currentData().toInt())).toString("hh:mm"));
	});
}

AlarmNotificationWindow::~AlarmNotificationWindow()
{
	delete ui;
}
