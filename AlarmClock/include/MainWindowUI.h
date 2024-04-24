#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QTreeView>
#include <QStandardItemModel>
#include <QScrollArea>
#include <QGroupBox>

#include "AlarmClock/AlarmsWidget.h"
#include "AlarmClock/IconPushButton.h"
#include "AlarmClock/AlarmScrollBar.h"

class MainWindowUI
{
public:
	void setupUI(QMainWindow* MainWindowClass);

	QWidget* centralWidget;
	QHBoxLayout* centralLayout;
	QWidget* functionSelectorWidget;
	AlarmsWidget* alarmsWidget;
	QVBoxLayout* alarmsListLayout;
	QWidget* alarmsManagerWidget;
	QHBoxLayout* alarmsManagerLayout;
	IconPushButton* deleteAlarmsButton;
	IconPushButton* confirmButton;
	IconPushButton* addAlarmButton;
	QVBoxLayout* verticalLayout;
	QWidget* alarmsChildWidget;
	QScrollArea* scrollArea;
	QVBoxLayout* alarmsChildLayout;
	QWidget* scrollAreaWidgetContents;

private:
	void setupAlarmClockUI();
};

namespace Ui {
	class MainWindowClass : public MainWindowUI {};
} // namespace Ui