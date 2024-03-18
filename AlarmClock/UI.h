#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

class UI
{
public:
	void setupMainWindowUI(QMainWindow* MainWindowClass);
	void setupSetAlarmWindowUI(QDialog* SetAlarmWindowClass);
	void setupAlarmClockWidgetUI(QWidget* AlarmClockWidgetClass);

	// MainWindow variables
	QWidget* mainWindowCentralWidget;
	QPushButton* mainWindowSetAlarmButton;
	QListWidget* alarmsListWidget;
	QVBoxLayout* vBoxLayout;

	// SetAlarmWindow variables
	QVBoxLayout* setAlarmWindowVLayout;
	QPushButton* setAlarmWindowSetAlarmButton;
	QLineEdit* lineEdit1;
	QLineEdit* lineEdit2;

	// AlarmClockWidget variables
	QGridLayout* gBoxLayout;
	QLabel* time;
	QLabel* name;
	QPushButton* testButton;

private:
	//QMainWindow* MainWindowClass;
	//QDialog* SetAlarmWindowClass;
	//QWidget* AlarmClockWidgetClass;
};

namespace Ui {
	class MainWindowClass : public UI {};
	class SetAlarmWindowClass : public UI {};
	class AlarmClockWidgetClass : public UI {};
} // namespace Ui