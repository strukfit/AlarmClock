#pragma once

#include <QTime>
#include <QTimer>
#include <QtWidgets/QMessageBox>

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
    void updateAlarm(const int& listId, const QString& name, const QTime& time);
    void deleteAlarm(const int& listId);
    void checkAlarm();
    void openAddAlarmWindow();
    void openEditAlarmWindow(const int& listId, const QString& name, const QTime& time);

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