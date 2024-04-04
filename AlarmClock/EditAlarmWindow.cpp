#include "EditAlarmWindow.h"

EditAlarmWindow::EditAlarmWindow(QWidget* parent, const int& listId, const QString& name, const QTime& time) :
	QDialog(parent),
	listId(listId)
{
	ui->setupEditAlarmWindowUI(this);

	ui->setValues(name, time);

	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);

	connect(ui->setAlarmButton, &QPushButton::clicked, this, [&] {
		int h = ui->hoursSpinBox->value();
		int m = ui->minutesSpinBox->value();

		QString name = ui->nameLineEdit->text();

		emit updateAlarm(this->listId, name, QTime(h, m));

		close();
	});

	connect(ui->cancelButton, &QPushButton::clicked, this, [&] {
		close();
	});

	connect(ui->deleteButton, &QPushButton::clicked, this, [&] {
		emit deleteAlarm(this->listId);

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
