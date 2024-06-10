#include "Timer/AddTimerWindow.h"

AddTimerWindow::AddTimerWindow(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::TimerWindowClass)
{
	ui->setupAddTimerWindowUI(this);

	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);

	this->setAttribute(Qt::WA_DeleteOnClose);

	connect(ui->setTimerButton, &QPushButton::clicked, this, [&] {
		int h = ui->hoursSpinBox->value();
		int m = ui->minutesSpinBox->value();
		int s = ui->secondsSpinBox->value();

		QString name = ui->nameLineEdit->text();

		emit setTimer(TimerWidget::lastId + 1, name, QTime(h, m, s));

		close();
	});

	connect(ui->cancelButton, &QPushButton::clicked, this, [&] {
		close();
	});
}

AddTimerWindow::~AddTimerWindow()
{
	delete ui;
}

void AddTimerWindow::setFocus()
{
	ui->hoursSpinBox->setFocus();
}
