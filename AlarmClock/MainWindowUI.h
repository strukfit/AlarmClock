#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

class MainWindowUI
{
public:
	void setupMainWindowUI(QMainWindow* MainWindowClass);

	QWidget* centralWidget;
	QPushButton* addAlarmButton;
	QListWidget* alarmsListWidget;
	QVBoxLayout* vBoxLayout;

};

namespace Ui {
	class MainWindowClass : public MainWindowUI {};
} // namespace Ui