#include "AlarmClock/ArrowPushButton.h"

ArrowPushButton::ArrowPushButton(QWidget* parent, bool upArrow) :
	QPushButton(parent),
	upArrow(upArrow)
{
	if(upArrow)
		setIcon(QIcon("Resources/arrow-up-grey.svg"));
	else
		setIcon(QIcon("Resources/arrow-down-grey.svg"));

	setStyleSheet("QPushButton { background-color: transparent; border-radius: 4px; } QPushButton:hover { background-color: #302c2c; } QPushButton:pressed { background-color: #282424; }");
}

void ArrowPushButton::mousePressEvent(QMouseEvent* event)
{
	QPushButton::mousePressEvent(event);

	if (upArrow)
		setIcon(QIcon("Resources/arrow-up-white.svg"));
	else
		setIcon(QIcon("Resources/arrow-down-white.svg"));
}

void ArrowPushButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);

	if (upArrow)
		setIcon(QIcon("Resources/arrow-up-grey.svg"));
	else
		setIcon(QIcon("Resources/arrow-down-grey.svg"));
}
