#include "AlarmClock/AlarmClockWidget.h"

int AlarmClockWidget::lastId = 0;

void AlarmClockWidget::mouseReleaseEvent(QMouseEvent* event)
{
	emit clicked(this);

	QWidget::mouseReleaseEvent(event);
}

bool AlarmClockWidget::event(QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		setStyleSheet("background-color: #2E2E2E; border-radius: 10px; border: 1px solid #363636;");
		
		QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
		shadowEffect->setBlurRadius(20);
		shadowEffect->setColor(QColor(0, 0, 0, 40));
		shadowEffect->setOffset(0, 7);

		this->setGraphicsEffect(shadowEffect);

		return true;
	}

	if (event->type() == QEvent::Leave)
	{
		setDefaultStyle();
		
		this->setGraphicsEffect(nullptr);
		
		return true;
	}
	return QWidget::event(event);
}

void AlarmClockWidget::setDefaultStyle()
{
	this->setStyleSheet("background-color: #323232; border-radius: 10px;");
}

AlarmClockWidget::AlarmClockWidget(QWidget* parent, int id, QTime time, QString name) :
	QWidget(parent), 
	ui(new Ui::AlarmClockWidgetClass), 
	id(id), 
	alarmTime(time), 
	name(name)
{
	ui->setupUI(this);
	setDefaultStyle();

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

void AlarmClockWidget::setInactiveColors()
{
	ui->time->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 60px; font-weight: bold; border: 0;");
	ui->name->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 20px; font-weight: bold; border: 0;");
}

void AlarmClockWidget::setActiveColors()
{
	if (isActive())
	{
		ui->time->setStyleSheet("background-color: transparent; color: white; font-size: 60px; font-weight: bold; border: 0;");
		ui->name->setStyleSheet("background-color: transparent; color: white; font-size: 20px; font-weight: bold; border: 0;");
	}
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

void AlarmClockWidget::setRemainingTime(QString time)
{
	ui->remainingTime->setText(time);
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
