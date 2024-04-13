#include "AlarmClock/AlarmsListWidget.h"

AlarmsListWidget::AlarmsListWidget(QWidget* parent) :
    QListWidget(parent)
{
}

void AlarmsListWidget::mousePressEvent(QMouseEvent* event)
{
    QListWidget::mousePressEvent(event);
}

void AlarmsListWidget::mouseMoveEvent(QMouseEvent* event)
{

    QListWidget::mouseMoveEvent(event);
}

//void AlarmsListWidget::enterEvent(QEnterEvent* event)
//{
//    QPoint pos = event->pos();
//
//    int leftMargin = 48;
//    int topMargin = 12;
//    int rightMargin = width() - 48;
//    int bottomMargin = 12;
//    
//    if (!(pos.x() >= leftMargin && pos.x() <= rightMargin &&
//        pos.y() >= topMargin && pos.y() <= bottomMargin)) {
//        QMessageBox::information(nullptr, "", "");
//        QListWidget::enterEvent(event);
//    }
//}
