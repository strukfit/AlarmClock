#include "Timer/TimerWidget.h"

int TimerWidget::lastId = 0;

TimerWidget::TimerWidget(QWidget* parent, int id, QTime time, QString name) :
	QWidget(parent),
	ui(new Ui::TimerWidgetClass),
	id(id),
	time(time),
	name(name),
	notifficationOpen(false)
{
	ui->setupUI(this);
	setDefaultStyle();

	ui->time->setText(time.toString("hh:mm:ss"));
	ui->name->setText(name);

	lastId++;
	
	//QObject::connect(ui->deleteButton, &QPushButton::clicked, [&] { emit deleteButtonClicked(this); });
}

void TimerWidget::mouseReleaseEvent(QMouseEvent* event)
{
	emit clicked(this);

	QWidget::mouseReleaseEvent(event);
}

bool TimerWidget::event(QEvent* event)
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

void TimerWidget::setDefaultStyle()
{
	this->setStyleSheet("background-color: #323232; border-radius: 10px;");
}

void TimerWidget::setActive(bool flag)
{
	
}

void TimerWidget::setName(const QString& name)
{
	this->name = name;
}

void TimerWidget::setTime(const QTime& time)
{
	this->time = time;
}

void TimerWidget::updateUI()
{
	ui->name->setText(name);
	ui->time->setText(time.toString("hh:mm::ss"));
}

void TimerWidget::setInactiveColors()
{
	ui->time->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 60px; font-weight: bold; border: 0;");
	ui->name->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 20px; font-weight: bold; border: 0;");
}

void TimerWidget::setActiveColors()
{
	if (isActive())
	{
		ui->time->setStyleSheet("background-color: transparent; color: white; font-size: 60px; font-weight: bold; border: 0;");
		ui->name->setStyleSheet("background-color: transparent; color: white; font-size: 20px; font-weight: bold; border: 0;");
	}
}

void TimerWidget::deleteMode(bool flag)
{
	if (flag)
	{
		setInactiveColors();
		ui->deleteButton->show();
	}
	else
	{
		setActiveColors();
		ui->deleteButton->hide();
	}
}

void TimerWidget::setNotificationOpen(bool flag)
{
	this->notifficationOpen = flag;
}

int TimerWidget::getId()
{
	return this->id;
}

QTime TimerWidget::getTime()
{
	return this->time;
}

QString TimerWidget::getName()
{
	return this->name;
}

bool TimerWidget::isActive()
{
	return false;
}

bool TimerWidget::isNotifficationOpen()
{
	return this->notifficationOpen;
}
