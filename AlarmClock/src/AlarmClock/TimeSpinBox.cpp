#include "AlarmClock/TimeSpinBox.h"

TimeSpinBox::TimeSpinBox(QWidget* parent, int min, int max) :
    QSpinBox(parent)
{
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setWrapping(true);
    setAlignment(Qt::AlignCenter);
    setRange(min, max);
    setPrefix("0");
    setReadOnly(true);
    setStyleSheet(R"(
        font-size: 40px; 
        font-weight: bold; 
        color: #a8a4a4; 
        background-color: transparent; 
        border: none; 
        border-radius: 3px;
    )");

    this->lineEdit()->setStyleSheet("selection-background-color: transparent;");

    connect(this, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        if (value < 10)
            setPrefix("0");
        else
            setPrefix("");
    });
}

TimeSpinBox::~TimeSpinBox()
{
}

void TimeSpinBox::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        stepBy(1);
        event->accept();
        break;
    case Qt::Key_Down:
        stepBy(-1);
        event->accept();
        break;
    default:
        if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) {
            QString currentValue = QString::number(value());

            if (value() > 9)
            {
                if (value() % 10 == 0 && event->key() != Qt::Key_0)
                    currentValue.remove(1, 1);
                else
                    currentValue.remove(0, 1);
            }

            currentValue.append(event->text());

            if (currentValue.toInt() <= maximum())
                setValue(currentValue.toInt());
            else
                setValue(event->text().toInt());

            event->accept();
            return;
        }
        break;
    }

    event->ignore();
    QSpinBox::keyPressEvent(event);
}

void TimeSpinBox::stepBy(int steps)
{
    int newValue = value() + steps;
    if (newValue < minimum())
        newValue = maximum();
    else if (newValue > maximum())
        newValue = minimum();
    setValue(newValue);
}

bool TimeSpinBox::event(QEvent* event)
{
    if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
        QPoint delta = wheelEvent->angleDelta() / 120;
        if (!delta.isNull()) {
            int numSteps = delta.y();
            stepBy(numSteps);
        }
        return true;
    }
    return QSpinBox::event(event);
}

void TimeSpinBox::focusInEvent(QFocusEvent* event)
{
    QSpinBox::focusInEvent(event);
    setStyleSheet(R"(
        font-size: 40px; 
        font-weight: bold; 
        color: white; 
        background-color: #302c2c; 
        border: none; 
        border-radius: 3px;
    )");

    if (parent() && parent()->parent()) {
        TimeWrapperWidget* wrapper = qobject_cast<TimeWrapperWidget*>(parent()->parent());
        if (wrapper)
            wrapper->childFocusIn();

        TimeWrapperChildWidget* wrapperChild = qobject_cast<TimeWrapperChildWidget*>(parentWidget());
        if (wrapperChild)
            wrapperChild->childFocusIn();
    }
}

void TimeSpinBox::focusOutEvent(QFocusEvent* event)
{
    QSpinBox::focusOutEvent(event);
    setStyleSheet(R"(
        font-size: 40px; 
        font-weight: bold; 
        color: #a8a4a4; 
        background-color: transparent; 
        border: none; 
        border-radius: 3px;
    )");

    if (parent() && parent()->parent()) {
        TimeWrapperWidget* wrapper = qobject_cast<TimeWrapperWidget*>(parent()->parent());
        if (wrapper)
            wrapper->childFocusOut();

        TimeWrapperChildWidget* wrapperChild = qobject_cast<TimeWrapperChildWidget*>(parentWidget());
        if (wrapperChild)
            wrapperChild->childFocusOut();
    }
}
