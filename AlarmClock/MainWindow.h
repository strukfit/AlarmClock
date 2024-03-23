#pragma once

#include <QTime>
#include <QTimer>
#include <QtWidgets/QMessageBox>

#include "MainWindowUI.h"
#include "SetAlarmWindow.h"
#include "AlarmClockWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void setAlarm(const QTime& time, const QString name);
    void checkAlarm();
    void openSetAlarmWindow();

signals:
    void childWindowShowed();

private:
    Ui::MainWindowClass* ui;

    SetAlarmWindow* setAlarmWindow;

    QWidget* overlayWidget;
};