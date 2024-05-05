#pragma once

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QBoxLayout>
#include <QPropertyAnimation>
#include <QLabel>
#include <QTime>
#include <QSvgWidget>

class CircularProgressBar : public QWidget {
    Q_OBJECT
    
public:
    CircularProgressBar(QWidget* parent = 0, int endValue = 0);

    void setEndValue(int endValue);
    void setInactiveColors(bool flag = true);

    void start();
    void stop();
    void pause();
    void resume();
    void restart();

    bool isRunning();
    bool isPaused();

    Q_SIGNAL void finished();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    void initAnimation();
    void init();

    int endValue;
    int currentValue;

    QPropertyAnimation* animation;
    QLabel* timeLabel;
    QTime time;
    QWidget* endTimeWidget;
    QLabel* endTimeLabel;

    bool running;
    bool paused;
};