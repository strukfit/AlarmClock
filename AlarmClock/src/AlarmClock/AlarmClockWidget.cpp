#include "AlarmClock/AlarmClockWidget.h"

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
	name(name)
{
	ui->setupAlarmClockWidgetUI(this);

	ui->time->setText(time.toString("hh:mm"));
	ui->name->setText(name);

	lastId++;

	QObject::connect(ui->toggleSwitch, &ToggleSwitch::toggled, [&] {
		if (ui->toggleSwitch->isChecked())
			setActiveColors();
		else
			setInactiveColors();
	});

	QObject::connect(ui->deleteButton, &QPushButton::clicked, [&] { emit deleteButtonClicked(this); });
}

void AlarmClockWidget::setActive(bool flag)
{
	this->ui->toggleSwitch->setChecked(flag);
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

void AlarmClockWidget::setInactiveColors()
{
	ui->time->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 50px; font-weight: bold;");
	ui->name->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 20px;");
}

void AlarmClockWidget::setActiveColors()
{
	ui->time->setStyleSheet("background-color: transparent; color: white; font-size: 50px; font-weight: bold;");
	ui->name->setStyleSheet("background-color: transparent; color: white; font-size: 20px;");
}

void AlarmClockWidget::deleteMode(bool flag)
{
	if (flag)
	{
		setInactiveColors();
		ui->toggleSwitch->hide();
		ui->deleteButton->show();
	}
	else
	{
		setActiveColors();
		ui->deleteButton->hide();
		ui->toggleSwitch->show();
	}
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
	return this->ui->toggleSwitch->isChecked();
}

QModelIndex AlarmClockWidget::getModelIndex()
{
	return this->modelIndex;
}
