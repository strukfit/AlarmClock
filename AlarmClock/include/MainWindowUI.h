#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QTreeView>
#include <QStandardItemModel>
#include <QScrollArea>
#include <QLabel>

#include "ResizableWidget.h"
#include "IconPushButton.h"
#include "CustomScrollBar.h"
#include "CheckableButton.h"

class MainWindowUI
{
public:
	void setupUI(QMainWindow* MainWindowClass);

	// General ui variables
	QWidget* centralWidget;
	QHBoxLayout* centralLayout;
	QWidget* functionSelectorWidget;
	IconPushButton* menuButton;
	CheckableButton* alarmClockButton;
	CheckableButton* timerButton;
	CheckableButton* stopwatchButton;
	CheckableButton* worldClockButton;

	// Alarm clock ui variables
	ResizableWidget* alarmsWidget;
	QVBoxLayout* alarmsListLayout;
	QWidget* alarmsManagerWidget;
	QHBoxLayout* alarmsManagerLayout;
	IconPushButton* deleteAlarmsButton;
	IconPushButton* confirmButton;
	IconPushButton* addAlarmButton;
	QVBoxLayout* alarmVLayout;
	QWidget* alarmsChildWidget;
	QVBoxLayout* alarmsChildLayout;

	// Timer ui variables
	ResizableWidget* timerWidget;
	QVBoxLayout* timerLayout;
	QWidget* timerChildWidget;
	QVBoxLayout* timerChildLayout;
	QScrollArea* timerScrollArea;
	QVBoxLayout* timerListLayout;
	QWidget* timerManagerWidget;
	QHBoxLayout* timerManagerLayout;
	IconPushButton* deleteTimerButton;
	IconPushButton* timerConfirmButton;
	IconPushButton* timerAddButton;

	// Stopwatch ui variables
	QWidget* stopwatchWidget;
	QVBoxLayout* stopwatchLayout;
	QLabel* stopwatchLabel;

	// World clock ui variables
	QWidget* worldClockWidget;
	QVBoxLayout* worldClockLayout;
	QLabel* worldClockLabel;

private:
	void setupAlarmClockUI();
	void setupTimerUI();
	void setupStopwatchUI();
	void setupWorldClockUI();
};

namespace Ui {
	class MainWindowClass : public MainWindowUI {};
} // namespace Ui