#pragma once

#include <QSpinBox>
#include <QKeyEvent>
#include <QMessageBox>

class TimeSpinBox : public QSpinBox {
public:
    TimeSpinBox(QWidget* parent = nullptr, int min = 0, int max = 59) : QSpinBox(parent), max(max) {
        setButtonSymbols(QAbstractSpinBox::NoButtons);
        setWrapping(true);
        setAlignment(Qt::AlignCenter);
        setRange(min, max);
        setPrefix("0");

        QObject::connect(this, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
            if (value < 10)
                setPrefix("0");
            else
                setPrefix("");
        });
    }

protected:
    void keyPressEvent(QKeyEvent* event) override {
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

            //QMessageBox::information(nullptr, "", currentValue);

            if (currentValue.toInt() <= max) 
            {
                setValue(currentValue.toInt());
            }  
            else
            {
                setValue(keyPressed);
                setPrefix("0");
            }

            event->accept();
            return;
        }

        // Вызываем обработчик событий базового класса
        QSpinBox::keyPressEvent(event);
    }

private:
    int max;
};