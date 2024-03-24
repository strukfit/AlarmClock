#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

class MainWindowUI
{
public:
	~MainWindowUI();

	void setupMainWindowUI(QMainWindow* MainWindowClass);

	QWidget* mainWindowCentralWidget;
	QPushButton* mainWindowSetAlarmButton;
	QListWidget* alarmsListWidget;
	QVBoxLayout* vBoxLayout;

};

namespace Ui {
	class MainWindowClass : public MainWindowUI {};
} // namespace Ui