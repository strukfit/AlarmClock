#include "Timer/EditTimerWindow.h"

EditTimerWindow::EditTimerWindow(QWidget* parent, TimerWidget* timer) :
	QDialog(parent),
	ui(new Ui::TimerWindowClass),
	timer(timer)
{
	ui->setupEditTimerWindowUI(this);

	ui->setValues(timer->getName(), timer->getTime());

	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);

	this->setAttribute(Qt::WA_DeleteOnClose);

	connect(ui->setTimerButton, &QPushButton::clicked, this, [&] {
		int h = ui->hoursSpinBox->value();
		int m = ui->minutesSpinBox->value();
		int s = ui->secondsSpinBox->value();

		QString name = ui->nameLineEdit->text();

		emit updateTimer(this->timer, name, QTime(h, m, s));

		close();
	});

	connect(ui->cancelButton, &QPushButton::clicked, this, [&] {
		close();
	});

	connect(ui->deleteButton, &QPushButton::clicked, this, [&] {
		emit deleteTimer(this->timer);

		close();
	});
}

EditTimerWindow::~EditTimerWindow()
{
	delete ui;
}

void EditTimerWindow::setFocus()
{
	ui->hoursSpinBox->setFocus();
}
