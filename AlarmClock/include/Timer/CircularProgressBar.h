#pragma once

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QMessageBox>

class CircularProgressBar : public QWidget {
    Q_OBJECT
    qreal p; // progress 0.0 to 1.0
    QPropertyAnimation* animation;
    int endValue;
public:
    CircularProgressBar(QWidget* parent = 0, int endValue = 0) : QWidget(parent), p(0), endValue(endValue) {
        setMinimumSize(208, 208);

        animation = new QPropertyAnimation(this, "p");
        animation->setStartValue(endValue);
        animation->setEndValue(0);
        animation->setDuration(endValue);
        animation->setEasingCurve(QEasingCurve::InOutQuad); 
        connect(animation, &QPropertyAnimation::valueChanged, this, [&](const QVariant& value) { 
            this->p = (qreal)value.toInt() / this->endValue; 
            this->update(); 
        });
        animation->start();
    }
    void paintEvent(QPaintEvent*) {
        qreal pd = p * 360;
        qreal rd = 360 - pd;
        QPainter p(this);
        p.fillRect(rect(), Qt::white);
        p.translate(10, 10);
        p.setRenderHint(QPainter::Antialiasing);
        QPainterPath path, path2;
        path.moveTo(100, 0);
        path.arcTo(QRectF(0, 0, 200, 200), 90, -pd);
        QPen pen, pen2;
        path2.moveTo(100, 0);
        pen2.setWidth(15);
        pen2.setColor(QColor("#3E3E3E"));
        pen2.setCapStyle(Qt::FlatCap);
        path2.arcTo(QRectF(0, 0, 200, 200), 90, rd);
        p.strokePath(path2, pen2);
        pen.setCapStyle(Qt::RoundCap);
        pen.setColor(QColor("#76B9ED"));
        pen.setWidth(15);
        p.strokePath(path, pen);
    }
};