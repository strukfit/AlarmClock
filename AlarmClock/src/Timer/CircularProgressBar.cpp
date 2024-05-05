#include "Timer/CircularProgressBar.h"

CircularProgressBar::CircularProgressBar(QWidget* parent, int endValue) :
    QWidget(parent),
    endValue(endValue),
    currentValue(0),
    running(false)
{
    setMinimumSize(208, 208);

    init();
}

void CircularProgressBar::setEndValue(int endValue)
{
    this->endValue = endValue;

    time = QTime(0, 0, 0).addMSecs(endValue);
    timeLabel->setText(time.toString("hh:mm:ss"));

    initAnimation();

    update();
}

void CircularProgressBar::setInactiveColors(bool flag)
{
    if (flag)
    {
        timeLabel->setStyleSheet("color: #7D7D7D; font-size: 40px; font-weight: bold; border: 0;");
        endTimeLabel->setStyleSheet("color: #7D7D7D; font-size: 12px; border: 0;");
    }
    else
    {
        timeLabel->setStyleSheet("color: white; font-size: 40px; font-weight: bold; border: 0;");
        endTimeLabel->setStyleSheet("color: white; font-size: 12px; border: 0;");
    }
}

void CircularProgressBar::start()
{
    animation->start();

    endTimeWidget->show();

    timeLabel->setStyleSheet("color: white; font-size: 40px; font-weight: bold; border: 0;");

    running = true;
    paused = false;
}

void CircularProgressBar::stop()
{
    animation->stop();

    running = false;
}

void CircularProgressBar::pause()
{
    animation->pause();

    endTimeWidget->hide();

    timeLabel->setStyleSheet("color: #D0D0D0; font-size: 40px; font-weight: bold; border: 0;");

    paused = true;
}

void CircularProgressBar::resume()
{
    animation->resume();

    endTimeWidget->show();

    timeLabel->setStyleSheet("color: white; font-size: 40px; font-weight: bold; border: 0;");

    paused = false;
}

void CircularProgressBar::restart()
{
    initAnimation();

    time = QTime(0, 0, 0).addMSecs(endValue);
    timeLabel->setText(time.toString("hh:mm:ss"));

    update();
}

bool CircularProgressBar::isRunning()
{
    return this->running;
}

bool CircularProgressBar::isPaused()
{
    return this->paused;
}

void CircularProgressBar::paintEvent(QPaintEvent*) {
    qreal pd = ((qreal)currentValue / endValue) * 360;
    qreal rd = 360 - pd;

    QPainter p(this);
    p.fillRect(rect(), Qt::transparent);
    p.setRenderHint(QPainter::Antialiasing);

    QPainterPath path, path2;
    path.moveTo(width() / 2, 10);
    path.arcTo(QRectF(10, 10, width() - 20, height() - 20), 90, -pd);

    QPen pen, pen2;
    path2.moveTo(width() / 2, 10);
    pen2.setWidth(15);
    pen2.setColor(QColor("#3E3E3E"));
    pen2.setCapStyle(Qt::FlatCap);

    path2.arcTo(QRectF(10, 10, width() - 20, height() - 20), 90, rd);
    p.strokePath(path2, pen2);
   
    if (running)
    {
        pen.setCapStyle(Qt::RoundCap);
        pen.setColor(QColor("#76B9ED"));
        timeLabel->setText(time.addMSecs(-(endValue - currentValue)).toString("hh:mm:ss"));
    }
    else
    {
        pen.setColor(QColor("#3E3E3E"));
        timeLabel->setText(time.toString("hh:mm:ss"));
    }

    pen.setWidth(15);
    p.strokePath(path, pen);

    int centerX = width() / 2;
    int centerY = height() / 2 ;

    int tCenterX = centerX - timeLabel->width() / 2;
    int tCenterY = centerY - timeLabel->height() / 2;

    timeLabel->move(tCenterX, tCenterY);

    int etX = centerX - endTimeWidget->width() / 2;
    int etY = centerY - endTimeWidget->height() / 2 + timeLabel->height()*0.8;

    endTimeWidget->move(etX, etY);

    endTimeLabel->setText(QTime::currentTime().addMSecs(endValue - currentValue).toString("hh:mm"));
}

void CircularProgressBar::initAnimation()
{
    animation = new QPropertyAnimation(this, "currentValue");
    animation->setStartValue(this->endValue);
    animation->setEndValue(0);
    animation->setDuration(this->endValue);

    connect(animation, &QPropertyAnimation::valueChanged, this, [&](const QVariant& value) {
        this->currentValue = value.toInt();
        this->update();
    });

    connect(animation, &QPropertyAnimation::finished, this, [&] { 
        emit finished(); 
        this->running = false;
    });
}

void CircularProgressBar::init()
{
    initAnimation();

    time = QTime(0, 0, 0).addMSecs(endValue);

    timeLabel = new QLabel("00:00:00", this);
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setStyleSheet("color: #D0D0D0; font-size: 40px; font-weight: bold; border: 0;");

    endTimeWidget = new QWidget(this);
    endTimeWidget->setFixedSize(QSize(67, 26));
    endTimeWidget->setStyleSheet("background-color: #3A3A3A; color: white; border-radius: 13px; border: 0;");

    auto layout = new QHBoxLayout(endTimeWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);
    layout->setAlignment(Qt::AlignCenter);

    QSvgWidget* alarmIcon = new QSvgWidget(endTimeWidget);
    alarmIcon->load(QString("Resources/alarm-white.svg"));
    alarmIcon->setStyleSheet("border: 0;");
    alarmIcon->setFixedSize(10, 10);

    layout->addWidget(alarmIcon);

    endTimeLabel = new QLabel(endTimeWidget);
    endTimeLabel->setStyleSheet("color: white; font-size: 12px; border: 0;");

    endTimeLabel->setText("00:00");

    layout->addWidget(endTimeLabel);

    endTimeWidget->hide();
}
