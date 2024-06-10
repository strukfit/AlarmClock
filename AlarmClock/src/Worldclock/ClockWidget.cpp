#include "Worldclock/ClockWidget.h"

int ClockWidget::lastId = 0;

ClockWidget::ClockWidget(QWidget* parent, int id, QByteArray timeZoneId) :
	QWidget(parent),
	ui(new Ui::ClockWidgetClass),
	id(id),
	timeZoneId(timeZoneId)
{
	ui->setupUI(this);
	setDefaultStyle();
	
	updateUI();

	lastId++;

	QObject::connect(ui->deleteButton, &QPushButton::clicked, [&] { emit deleteButtonClicked(this); });
}

bool ClockWidget::event(QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		setStyleSheet(R"(
			QWidget {
				background-color: #2E2E2E; 
				border-radius: 10px; 
				border: 1px solid #363636;
			}			

			QToolTip {
				background-color: #2C2C2C;
				color: white;
				border-radius: 0; 
				border: 1px solid #282828;
			}
		)");

		return true;
	}

	if (event->type() == QEvent::Leave)
	{
		setDefaultStyle();

		return true;
	}
	return QWidget::event(event);
}

void ClockWidget::setDefaultStyle()
{
	this->setStyleSheet(R"(
		QWidget {
			background-color: #323232; 
			border-radius: 10px; 
			border: 1px solid #242424;
		}
	)");
}

void ClockWidget::setTimeZoneId(const QByteArray& timeZoneId)
{
	this->timeZoneId = timeZoneId;
}

void ClockWidget::updateUI()
{
	QTimeZone timeZone = QTimeZone(timeZoneId);

	if (timeZone.isValid())
	{
		QDateTime utcDateTime = QDateTime::currentDateTime();
		QDateTime localDateTime = utcDateTime.toTimeZone(timeZone);

		QTime time = localDateTime.time();
		QDate date = localDateTime.date();

		ui->time->setText(time.toString("hh:mm"));
		ui->date->setText(date.toString("dd.MM.yyyy"));

		QString name;
		QString displayName;

		if (timeZoneId.compare(QTimeZone::systemTimeZoneId()) == 0)
		{
			name = "Local time";
			displayName = name;
		}
		else 
		{
			QString city = QString(timeZone.id()).section('/', 1, 1);
			QString region = QString(timeZone.id()).section('/', 0, 0);
			name = city;
			displayName = QString("%1, %2").arg(city, region);
		}
		
		ui->name->setText(name);

		QString description = QString("%1, %2, %3")
			.arg(displayName, time.toString("h:mm"), date.toString("d MMMM yyyy") + " y.");

		this->setToolTip(description);

		QTime nightStartTime(22, 0);
		QTime nightEndTime(6, 0);

		if (time >= nightStartTime || time <= nightEndTime)
		{
			ui->dayIcon->hide();
			ui->nightIcon->show();
		}
		else
		{
			ui->nightIcon->hide();
			ui->dayIcon->show();
		}
	}
}

void ClockWidget::deleteMode(bool flag)
{
	ui->deleteButton->setHidden(!flag);
}

int ClockWidget::getId()
{
	return this->id;
}

QByteArray ClockWidget::getTimeZoneId()
{
	return this->timeZoneId;
}