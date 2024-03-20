#pragma once

#include <QSpinBox>
#include <QKeyEvent>
#include <QMessageBox>
#include <QLineEdit>

#include "TimeWrapperWidget.h"

class TimeSpinBox : public QSpinBox {
    Q_OBJECT

public:
    TimeSpinBox(QWidget* parent = nullptr, int min = 0, int max = 59);
    ~TimeSpinBox();

protected:
    void keyPressEvent(QKeyEvent* event) override;

    void stepBy(int steps) override;

    bool event(QEvent* event) override;

    void focusInEvent(QFocusEvent* event) override;

    void focusOutEvent(QFocusEvent* event) override;
};