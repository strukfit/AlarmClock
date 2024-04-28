#include "AlarmClock/EditAlarmWindow.h"

EditAlarmWindow::EditAlarmWindow(QWidget* parent, AlarmClockWidget* alarm) :
	QDialog(parent),
	alarm(alarm)
{
	ui->setupEditAlarmWindowUI(this);

	ui->setValues(alarm->getName(), alarm->getAlarmTime());

	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);

	this->setAttribute(Qt::WA_DeleteOnClose);

	connect(ui->setAlarmButton, &QPushButton::clicked, this, [&] {
		int h = ui->hoursSpinBox->value();
		int m = ui->minutesSpinBox->value();

		QString name = ui->nameLineEdit->text();

		emit updateAlarm(this->alarm, name, QTime(h, m));

		this->alarm->setActive(true);

		close();
	});

	connect(ui->cancelButton, &QPushButton::clicked, this, [&] {
		close();
	});

	connect(ui->deleteButton, &QPushButton::clicked, this, [&] {
		emit deleteAlarm(this->alarm);

		close();
	});
}

EditAlarmWindow::~EditAlarmWindow()
{
	delete ui;
}

void EditAlarmWindow::setFocus()
{
	ui->hoursSpinBox->setFocus();
}
