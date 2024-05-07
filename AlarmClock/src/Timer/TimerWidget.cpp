#include "Timer/TimerWidget.h"

int TimerWidget::lastId = 0;

TimerWidget::TimerWidget(QWidget* parent, int id, QTime time, QString name) :
	QWidget(parent),
	ui(new Ui::TimerWidgetClass),
	id(id),
	time(time),
	name(name)
{
	ui->setupUI(this);
	setDefaultStyle();

	ui->name->setText(name);

	int total = QTime(0, 0, 0).msecsTo(getTime());

	ui->progressBar->setEndValue(total);

	connect(ui->playButton, &QPushButton::clicked, this, [&] {
		ui->progressBar->start();

		ui->playButton->hide();
		ui->pauseButton->show();
	});
	
	connect(ui->pauseButton, &QPushButton::clicked, this, [&] {
		ui->progressBar->pause();

		ui->pauseButton->hide();
		ui->playButton->show();
	});
	
	connect(ui->restartButton, &QPushButton::clicked, this, [&] {
		ui->progressBar->restart();

		if (!ui->progressBar->isPaused())
		{
			ui->progressBar->start();
		}
		else
		{
			ui->progressBar->stop();
		}
	});

	lastId++;

	QObject::connect(ui->progressBar, &CircularProgressBar::finished, [&] { emit expired(this); });
	QObject::connect(ui->deleteButton, &QPushButton::clicked, [&] { emit deleteButtonClicked(this); });
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

	if (event->type() == QEvent::Resize)
	{
		ui->deleteButton->move(this->width() - ui->deleteButton->width() - 5, 5);

		return true;
	}

	return QWidget::event(event);
}

void TimerWidget::setDefaultStyle()
{
	this->setStyleSheet("background-color: #323232; border-radius: 10px; border: 0;");
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

	int total = QTime(0, 0, 0).msecsTo(getTime());
	ui->progressBar->setEndValue(total);
}

void TimerWidget::setInactiveColors()
{
	ui->name->setStyleSheet("background-color: transparent; color: #7D7D7D; font-size: 14px; font-weight: bold; border: 0;");
}

void TimerWidget::setActiveColors()
{
	ui->name->setStyleSheet("background-color: transparent; color: white; font-size: 14px; font-weight: bold; border: 0;");
}

void TimerWidget::deleteMode(bool flag)
{
	if (flag)
	{
		ui->deleteButton->show();

		setInactiveColors();
		ui->progressBar->setInactiveColors(true);

		ui->playButton->setDisabled(true);
		ui->pauseButton->setDisabled(true);
		ui->restartButton->setDisabled(true);

		ui->playButton->setInactiveIcon(true);
		ui->pauseButton->setInactiveIcon(true);
		ui->restartButton->setInactiveIcon(true);
	}
	else
	{
		ui->deleteButton->hide();

		setActiveColors();
		ui->progressBar->setInactiveColors(false);

		ui->playButton->setDisabled(false);
		ui->pauseButton->setDisabled(false);
		ui->restartButton->setDisabled(false);

		ui->playButton->setInactiveIcon(false);
		ui->pauseButton->setInactiveIcon(false);
		ui->restartButton->setInactiveIcon(false);
	}
}

void TimerWidget::showPlayButton()
{
	ui->pauseButton->hide();
	ui->playButton->show();
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

