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