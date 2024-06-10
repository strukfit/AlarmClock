#pragma once

#include <QTime>
#include <QTimer>
#include <QtWidgets/QMessageBox>
#include <QSettings>

#include "MainWindowUI.h"
#include "DatabaseManager.h"

#include "AlarmClock/AddAlarmWindow.h"
#include "AlarmClock/EditAlarmWindow.h"
#include "AlarmClock/AlarmClockWidget.h"
#include "AlarmClock/AlarmNotificationWindow.h"

#include "Timer/TimerWidget.h"
#include "Timer/AddTimerWindow.h"
#include "Timer/EditTimerWindow.h"
#include "Timer/TimerNotificationWindow.h"

#include "WorldClock/AddClockWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    AlarmClockWidget* setAlarm(const int& id, const QString& name, const QTime& time);
    TimerWidget* setTimer(const int& id, const QString& name, const QTime& time);
    ClockWidget* addClock(const int& id, const QByteArray& timeZoneId);
    void updateAlarm(AlarmClockWidget* alarm, const QString& name, const QTime& time);
    void updateTimer(TimerWidget* timer, const QString& name, const QTime& time);
    void deleteAlarm(AlarmClockWidget* alarm);
    void deleteTimer(TimerWidget* timer);
    void deleteClock(ClockWidget* clock);
    void checkAlarm();
    void openAddAlarmWindow();
    void openAddTimerWindow();
    void openEditAlarmWindow(AlarmClockWidget* alarm);
    void openEditTimerWindow(TimerWidget* timer);
    void openTimerNotificationWindow(TimerWidget* timer);
    void openAddClockWindow();
    void decreaseMenu();
    void stopwatchUpdateTime();
    void cutoffTableCalculations();

signals:
    void childWindowShowed();
    void alarmClockAdded(const int& id, const QString& name, const QTime& time);
    void alarmClockUpdated(const int& id, const QString& name, const QTime& time);
    void alarmClockDeleted(const int& id);
    void timerAdded(const int& id, const QString& name, const QTime& time);
    void clockAdded(const int& id, const QByteArray& timeZoneId);
    void timerUpdated(const int& id, const QString& name, const QTime& time);
    void timerDeleted(const int& id);
    void clockDeleted(const int& id);
    void closed();

protected:
    void closeEvent(QCloseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void setSideMenuConnections();
    void setAlarmClockConnections();
    void setTimerConnections();
    void setStopwatchConnections();
    void setWorldClockConnections();

    void increaseMenu();

    Ui::MainWindowClass* ui;

    DatabaseManager* dbManager;

    QWidget* overlayWidget;
    QTimer* timer;
    QTimer* stopwatchTimer;
    QElapsedTimer* stopwatchElapsedTimer;

    bool menuExpanded;
    qint64 stopwatchTime;
    qint64 cutoffTime;
    //QString settingsFile = QApplication::applicationDirPath() + "/settings.ini";
};