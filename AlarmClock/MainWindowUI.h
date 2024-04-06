#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QGraphicsDropShadowEffect>

#include "AlarmsWidget.h"
#include "IconPushButton.h"
#include "AlarmsListWidget.h"

class MainWindowUI
{
public:
	void setupMainWindowUI(QMainWindow* MainWindowClass);

	QWidget* centralWidget;
	QHBoxLayout* centralLayout;
	QWidget* functionSelectorWidget;
	AlarmsWidget* alarmsWidget;
	QListWidget* alarmsListWidget;
	QVBoxLayout* alarmsListLayout;
	QWidget* alarmsManagerWidget;
	QHBoxLayout* alarmsManagerLayout;
	IconPushButton* deleteAlarmsButton;
	IconPushButton* confirmButton;
	IconPushButton* addAlarmButton;

};

namespace Ui {
	class MainWindowClass : public MainWindowUI {};
} // namespace Ui