#include "AlarmClockWidget.h"

int AlarmClockWidget::count = 0;

AlarmClockWidget::AlarmClockWidget(QWidget* parent, int id, QTime time, QString name) :
	QWidget(parent), 
	ui(new Ui::AlarmClockWidgetClass), 
	id(id), 
	alarmTime(time), 
	name(name), 
	active(true)
{
	ui->setupAlarmClockWidgetUI(this);

	ui->time->setText(time.toString("hh:mm"));
	ui->name->setText(name);

	count++;
}

void AlarmClockWidget::setActive(bool flag)
{
	this->active = flag;
}

void AlarmClockWidget::setName(const QString& name)
{
	this->name = name;
}

void AlarmClockWidget::setAlarmTime(const QTime& alarmTime)
{
	this->alarmTime = alarmTime;
}

void AlarmClockWidget::updateUI()
{
	ui->name->setText(name);
	ui->time->setText(alarmTime.toString("hh:mm"));
}

int AlarmClockWidget::getId()
{
	return this->id;
}

QTime AlarmClockWidget::getAlarmTime()
{
	return this->alarmTime;
}

QString AlarmClockWidget::getName()
{
	return this->name;
}

bool AlarmClockWidget::isActive()
{
	return this->active;
}