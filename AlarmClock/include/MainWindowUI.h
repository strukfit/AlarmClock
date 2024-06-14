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
#include <QTableWidget>
#include <QHeaderView>
#include <QTimeZone>

#include "ResizableWidget.h"
#include "IconPushButton.h"
#include "CustomScrollBar.h"
#include "CheckableButton.h"
#include "Worldclock/ClockWidget.h"

class MainWindowUI
{
public:
	void setupUI(QMainWindow* MainWindowClass);

	// General ui variables
	QWidget* centralWidget;
	QHBoxLayout* centralLayout;
	
	// Menu ui variables
	struct MenuUI {
		QWidget* centralWidget;
		IconPushButton* menuButton;
		CheckableButton* alarmClockButton;
		CheckableButton* timerButton;
		CheckableButton* stopwatchButton;
		CheckableButton* worldClockButton;
	} MenuUI;

	// Alarm clock ui variables
	struct AlarmClockUI {
		ResizableWidget* centralWidget;
		QVBoxLayout* listLayout;
		QWidget* managerWidget;
		QHBoxLayout* managerLayout;
		IconPushButton* deleteButton;
		IconPushButton* confirmButton;
		IconPushButton* addButton;
		QVBoxLayout* layout;
		QWidget* childWidget;
		QVBoxLayout* childLayout;
	} AlarmClockUI;

	// Timer ui variables
	struct TimerUI {
		ResizableWidget* centralWidget;
		QVBoxLayout* layout;
		QWidget* childWidget;
		QVBoxLayout* childLayout;
		QScrollArea* scrollArea;
		QVBoxLayout* listLayout;
		QWidget* managerWidget;
		QHBoxLayout* managerLayout;
		IconPushButton* deleteButton;
		IconPushButton* confirmButton;
		IconPushButton* addButton;
	} TimerUI;

	// Stopwatch ui variables
	struct StopwatchUI {
		QWidget* centralWidget;
		QVBoxLayout* layout;
		QLabel* label;
		QLabel* hLabel;
		QLabel* mLabel;
		QLabel* sLabel;
		IconPushButton* startButton;
		IconPushButton* pauseButton;
		IconPushButton* resetButton;
		IconPushButton* cutoffButton;
		QTableWidget* cutoffTable;
	} StopwatchUI;

	// World clock ui variables
	struct WorldClockUI {
		ResizableWidget* centralWidget;
		QVBoxLayout* layout;
		QWidget* childWidget;
		QVBoxLayout* childLayout;
		QVBoxLayout* listLayout;
		QWidget* managerWidget;
		QHBoxLayout* managerLayout;
		IconPushButton* deleteButton;
		IconPushButton* confirmButton;
		IconPushButton* addButton;
	} WorldClockUI;

private:
	void setupAlarmClockUI();
	void setupTimerUI();
	void setupStopwatchUI();
	void setupWorldClockUI();
};

namespace Ui {
	class MainWindowClass : public MainWindowUI {};
} // namespace Ui