#include "SetAlarmWindow.h"

SetAlarmWindow::SetAlarmWindow(QWidget* parent) :
	QDialog(parent), ui(new Ui::SetAlarmWindowClass)
{
	ui->setupSetAlarmWindowUI(this);

	connect(ui->setAlarmWindowSetAlarmButton, &QPushButton::pressed, this, [&] {
		//int h = ui->lineEdit1->text().toInt();
		//int m = ui->lineEdit2->text().toInt();		
		
		//int h = ui->hourSpinBox->value();
		//int m = ui->minutesSpinBox->value();
		//QMessageBox::information(nullptr, "", QString::number(h));
		//emit setAlarm(QTime(h, m));

		close();
	});
}

SetAlarmWindow::~SetAlarmWindow()
{
	delete ui;
}