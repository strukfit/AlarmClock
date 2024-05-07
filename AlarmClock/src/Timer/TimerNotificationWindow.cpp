#include "Timer/TimerNotificationWindow.h"

TimerNotificationWindow::TimerNotificationWindow(QMainWindow* parent, TimerWidget* timer) :
	QDialog(parent),
	ui(new Ui::TimerNotificationWindowClass)
{
	ui->setupUI(this);

	setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);

	ui->name->setText(timer->getName());
	ui->time->setText(timer->getTime().toString("hh:mm:ss"));

	this->setAttribute(Qt::WA_DeleteOnClose);

	connect(ui->closeButton, &QPushButton::clicked, this, &QDialog::close);
	
	alarmSound = new QSoundEffect(this);
	alarmSound->setSource(QUrl::fromLocalFile("Resources/alarm.wav"));
	alarmSound->setLoopCount(QSoundEffect::Infinite);
	alarmSound->setVolume(0.25f);

	alarmSound->play();

	connect(this, &TimerNotificationWindow::resized, this, [&] {
		QSize s = this->size();
		ui->muteButton->move(s.width() - ui->muteButton->frameSize().width() - 2, 2);
		ui->unmuteButton->move(s.width() - ui->unmuteButton->frameSize().width() - 2, 2);
	});

	connect(ui->muteButton, &QPushButton::clicked, [&] {
		this->alarmSound->stop();
		ui->muteButton->hide();
		ui->unmuteButton->show();
	});

	connect(ui->unmuteButton, &QPushButton::clicked, [&] {
		this->alarmSound->play();
		ui->unmuteButton->hide();
		ui->muteButton->show();
	});
}

TimerNotificationWindow::~TimerNotificationWindow()
{
	alarmSound->stop();

	delete ui;
}

void TimerNotificationWindow::resizeEvent(QResizeEvent* event)
{
	emit resized();
	QDialog::resizeEvent(event);
}