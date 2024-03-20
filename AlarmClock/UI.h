#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtSvgWidgets/QSvgWidget>
#include <QtSvg/QSvgRenderer>

#include "TimeSpinBox.h"
#include "TimeWrapperWidget.h"
#include "ArrowPushButton.h"
#include "NameLineEdit.h"
#include "XPushButton.h"

class UI
{
public:
	~UI();

	void setupMainWindowUI(QMainWindow* MainWindowClass);
	void setupSetAlarmWindowUI(QDialog* SetAlarmWindowClass);
	void setupAlarmClockWidgetUI(QWidget* AlarmClockWidgetClass);

	// MainWindow variables
	QWidget* mainWindowCentralWidget;
	QPushButton* mainWindowSetAlarmButton;
	QListWidget* alarmsListWidget;
	QVBoxLayout* vBoxLayout;

	// SetAlarmWindow variables
	QLabel* title;
	QVBoxLayout* setAlarmWindowVLayout;
	QPushButton* setAlarmWindowSetAlarmButton;
	QHBoxLayout* timeSelectorHBoxLayout;
	TimeWrapperWidget* timeWrapperWidget;
	TimeWrapperChildWidget* timeSelectorWidget;
	TimeSpinBox* hourSpinBox;
	TimeSpinBox* minutesSpinBox;
	QLabel* separatorLabel;
	QHBoxLayout* editNameHBoxLayout;
	QSvgWidget* editSvgWidget;
	NameLineEdit* nameLineEdit;
	ArrowPushButton* arrowUpButton1;
	ArrowPushButton* arrowUpButton2;
	ArrowPushButton* arrowDownButton1;
	ArrowPushButton* arrowDownButton2;
	TimeWrapperWidget* editNameWrapperWidget;
	TimeWrapperChildWidget* editNameWidget;
	QHBoxLayout* nameLineEditLayout;
	XPushButton* xButton;

	// AlarmClockWidget variables
	QGridLayout* gBoxLayout;
	QLabel* time;
	QLabel* name;
	QPushButton* testButton;

private:
	const QString activeAccentColor = "#78bcec";
	const QString inactiveAccentColor = "#9c9c9c";

	static int defaultNameCounter;
	QString defaultName = "Alarm clock";
};

namespace Ui {
	class MainWindowClass : public UI {};
	class SetAlarmWindowClass : public UI {};
	class AlarmClockWidgetClass : public UI {};
} // namespace Ui