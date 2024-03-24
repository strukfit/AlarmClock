#include "SetAlarmWindow.h"

SetAlarmWindow::SetAlarmWindow(QWidget* parent) :
	QDialog(parent), ui(new Ui::SetAlarmWindowClass)
{
	ui->setupSetAlarmWindowUI(this);

	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);
	//setWindowFlags(Qt::Popup);

	connect(ui->setAlarmButton, &QPushButton::clicked, this, [&] {
		int h = ui->hoursSpinBox->value();
		int m = ui->minutesSpinBox->value();

		QString name = ui->nameLineEdit->text();

		emit setAlarm(AlarmClockWidget::count + 1, name, QTime(h, m));

		close();
	});

	connect(ui->cancelButton, &QPushButton::clicked, this, [&] {
		close();
	});
}

SetAlarmWindow::~SetAlarmWindow()
{
	delete ui;
}

void SetAlarmWindow::setDefaultValues()
{
	ui->setDefaultTime();
	ui->setDefaultName();
}

void SetAlarmWindow::setDefaultFocus()
{
	ui->hoursSpinBox->setFocus();
}
