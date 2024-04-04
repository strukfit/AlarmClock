#include "EditAlarmWindow.h"

EditAlarmWindow::EditAlarmWindow(QWidget* parent, const int& listId) :
	QDialog(parent),
	listId(listId)
{
	ui->setupEditAlarmWindowUI(this);

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

void EditAlarmWindow::setValues(const QString& name, const QTime& time)
{
	ui->hoursSpinBox->setValue(time.hour());
	ui->minutesSpinBox->setValue(time.minute());

	ui->nameLineEdit->setText(name);
}

void EditAlarmWindow::setFocus()
{
	ui->hoursSpinBox->setFocus();
}
