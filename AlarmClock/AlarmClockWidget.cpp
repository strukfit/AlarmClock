#include "AlarmClockWidget.h"

int AlarmClockWidget::lastId = 0;

void AlarmClockWidget::mouseReleaseEvent(QMouseEvent* event)
{
	emit clicked(this);

	QWidget::mouseReleaseEvent(event);
}

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

	lastId++;
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

void AlarmClockWidget::setModelIndex(const QModelIndex& modelIndex)
{
	this->modelIndex = modelIndex;
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

QModelIndex AlarmClockWidget::getModelIndex()
{
	return this->modelIndex;
}
