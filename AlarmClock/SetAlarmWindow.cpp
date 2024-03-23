#include "SetAlarmWindow.h"

SetAlarmWindow::SetAlarmWindow(QWidget* parent) :
	QDialog(parent), ui(new Ui::SetAlarmWindowClass)
{
	ui->setupSetAlarmWindowUI(this);

	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);
	//setWindowFlags(Qt::Popup);

	connect(ui->setAlarmButton, &QPushButton::clicked, this, [&] {
		
		int h = ui->hourSpinBox->value();
		int m = ui->minutesSpinBox->value();

		QString name = ui->nameLineEdit->text();

		emit setAlarm(QTime(h, m), name);

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
	ui->hourSpinBox->setFocus();
}
