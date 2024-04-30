#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>

#include "IconPushButton.h"

class TimerWidgetUI
{
public:
	void setupUI(QWidget* TimerWidget);

	QWidget* centralWidget;
	QGridLayout* gBoxLayout;
	QLabel* time;
	QLabel* name;
	IconPushButton* deleteButton;
};

namespace Ui {
	class TimerWidgetClass : public TimerWidgetUI {};
} // namespace Ui