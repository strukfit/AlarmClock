#include "EditAlarmWindow.h"

EditAlarmWindow::EditAlarmWindow(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::SetAlarmWindowClass)
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

void EditAlarmWindow::setListId(const int& listId)
{
	this->listId = listId;
}
