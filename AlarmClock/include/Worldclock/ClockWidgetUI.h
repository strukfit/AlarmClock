#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>

#include "IconPushButton.h"

class ClockWidgetUI
{
public:
	void setupUI(QWidget* ClockWidgetClass);

	QHBoxLayout* layout;
	QSvgWidget* dayIcon;
	QSvgWidget* nightIcon;
	QLabel* time;
	QLabel* name;
	QLabel* date;
	IconPushButton* deleteButton;
};

namespace Ui {
	class ClockWidgetClass : public ClockWidgetUI {};
} // namespace Ui