#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>

#include "IconPushButton.h"
#include "Timer/CircularProgressBar.h"

class TimerWidgetUI
{
public:
	void setupUI(QWidget* TimerWidget);

	QVBoxLayout* layout;
	QLabel* name;
	IconPushButton* deleteButton;
	CircularProgressBar* progressBar;
	IconPushButton* playButton;
	IconPushButton* pauseButton;
	IconPushButton* restartButton;
};

namespace Ui {
	class TimerWidgetClass : public TimerWidgetUI {};
} // namespace Ui