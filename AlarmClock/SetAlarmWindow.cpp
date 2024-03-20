#include "SetAlarmWindow.h"

SetAlarmWindow::SetAlarmWindow(QWidget* parent) :
	QDialog(parent), ui(new Ui::SetAlarmWindowClass)
{
	ui->setupSetAlarmWindowUI(this);

	connect(ui->setAlarmWindowSetAlarmButton, &QPushButton::pressed, this, [&] {	
		
		int h = ui->hourSpinBox->value();
		int m = ui->minutesSpinBox->value();

		QString name = ui->nameLineEdit->text();

		emit setAlarm(QTime(h, m), name);

		close();
	});
}

SetAlarmWindow::~SetAlarmWindow()
{
	delete ui;
}