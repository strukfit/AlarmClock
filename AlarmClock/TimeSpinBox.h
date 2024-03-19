#pragma once

#include <QSpinBox>
#include <QKeyEvent>
#include <QMessageBox>

class TimeSpinBox : public QSpinBox {
public:
    TimeSpinBox(QWidget* parent = nullptr, int min = 0, int max = 59) : QSpinBox(parent) {
        setButtonSymbols(QAbstractSpinBox::NoButtons);
        setWrapping(true);
        setAlignment(Qt::AlignCenter);
        setRange(min, max);
        setPrefix("0");
        setReadOnly(true);

        QObject::connect(this, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
            if (value < 10)
                setPrefix("0");
            else
                setPrefix("");
        });
    }
    
protected:
    void keyPressEvent(QKeyEvent* event) override {
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
            int keyPressed = event->text().toInt();
            if (keyPressed >= 0 && keyPressed <= 9) {
                QString currentValue = QString::number(value());

                if (value() > 9)
                {
                    if (value() % 10 == 0)
                        currentValue.remove(1, 1);
                    else
                        currentValue.remove(0, 1);
                }

                currentValue.append(event->text());

                if (currentValue.toInt() <= maximum())
                {
                    setValue(currentValue.toInt());
                }
                else
                {
                    setValue(keyPressed);
                }

                event->accept();
                return;
            }
            break;
        }

        QSpinBox::keyPressEvent(event);
    }

    void stepBy(int steps) override {
        int newValue = value() + steps;
        if (newValue < minimum())
            newValue = maximum();
        else if (newValue > maximum())
            newValue = minimum();
        setValue(newValue);
    }

    bool event(QEvent* event) override {
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
};