#pragma once

#include <QTime>
#include <QTimer>
#include <QtWidgets/QMessageBox>

#include "MainWindowUI.h"
#include "SetAlarmWindow.h"
#include "AlarmClockWidget.h"
#include "DatabaseManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void setAlarm(const int& id, const QString& name, const QTime& time);
    void checkAlarm();
    void openSetAlarmWindow();

signals:
    void childWindowShowed();
    void alarmClockAdded(const int& id, const QString& name, const QTime& time);

private:
    Ui::MainWindowClass* ui;

   DatabaseManager* dbManager;

    SetAlarmWindow* setAlarmWindow;

    QWidget* overlayWidget;
};