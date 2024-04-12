#pragma once

#include <QTime>
#include <QTimer>
#include <QtWidgets/QMessageBox>
#include <QSettings>

#include "MainWindowUI.h"
#include "AddAlarmWindow.h"
#include "EditAlarmWindow.h"
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
    void updateAlarm(AlarmClockWidget* alarm, const QString& name, const QTime& time);
    void deleteAlarm(AlarmClockWidget* alarm);
    void checkAlarm();
    void openAddAlarmWindow();
    void openEditAlarmWindow(AlarmClockWidget* alarm);

signals:
    void childWindowShowed();
    void alarmClockAdded(const int& id, const QString& name, const QTime& time);
    void alarmClockUpdated(const int& id, const QString& name, const QTime& time);
    void alarmClockDeleted(const int& id);

private:
    Ui::MainWindowClass* ui;

    DatabaseManager* dbManager;

    QWidget* overlayWidget;
};