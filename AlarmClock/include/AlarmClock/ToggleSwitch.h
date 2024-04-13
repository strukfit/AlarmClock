/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include <QWidget>

class ToggleSwitch : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)
public:
    explicit ToggleSwitch(QWidget* parent = nullptr, QString accentColor = "#000");

    void setChecked(bool checked);
    bool isChecked() const;

    void toggle();

    QSize sizeHint() const override;

signals:
    void checked(bool checked); // by user
    void toggled(bool checked); // by user or by program

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    bool m_checked = false;
    bool m_mouseDown = false;

    QString backgroundColor = "#2D2D2D";
    QString outlineColor = "#A1A1A1";
    QString accentColor;
};

#endif // TOGGLESWITCH_H