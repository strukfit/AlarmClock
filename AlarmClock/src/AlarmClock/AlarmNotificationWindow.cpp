#include "AlarmClock/AlarmNotificationWindow.h"

AlarmNotificationWindow::AlarmNotificationWindow(QMainWindow* parent, AlarmClockWidget* alarm) :
	QDialog(parent),
	ui(new Ui::AlarmNotificationWindowClass),
	alarm(alarm)
{
	ui->setupUI(this);

	setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);

	ui->name->setText(alarm->getName());
	ui->time->setText(alarm->getAlarmTime().toString("hh:mm"));

	ui->snoozeComboBox->addItem("5 minutes", 300);
	ui->snoozeComboBox->addItem("10 minutes", 600);
	ui->snoozeComboBox->addItem("20 minutes", 1200);
	ui->snoozeComboBox->addItem("30 minutes", 1800);
	ui->snoozeComboBox->addItem("1 hour", 3600);

	ui->snoozeComboBox->setCurrentIndex(1);

	this->setAttribute(Qt::WA_DeleteOnClose);

	connect(ui->snoozeButton, &QPushButton::clicked, this, [&] {
		this->alarm->setAlarmTime(this->alarm->getAlarmTime().addSecs(this->ui->snoozeComboBox->currentData().toInt()));
		this->alarm->updateUI();
		emit alarmSnoozed(this->alarm->getId(), this->alarm->getName(), this->alarm->getAlarmTime());
		close();
	});

	connect(ui->closeButton, &QPushButton::clicked, this, &QDialog::close);

	alarm->setNotificationOpen(true);

	alarmSound = new QSoundEffect(this);
	alarmSound->setSource(QUrl::fromLocalFile("Resources/alarm.wav"));
	alarmSound->setLoopCount(QSoundEffect::Infinite);
	alarmSound->setVolume(0.25f);

	alarmSound->play();

	connect(this, &AlarmNotificationWindow::resized, this, [&] {
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

AlarmNotificationWindow::~AlarmNotificationWindow()
{
	alarmSound->stop();

	delete ui;

	this->alarm->setNotificationOpen(false);
}

void AlarmNotificationWindow::resizeEvent(QResizeEvent* event)
{
	emit resized();
	QDialog::resizeEvent(event);
}