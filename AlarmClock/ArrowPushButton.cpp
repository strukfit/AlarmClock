#include "ArrowPushButton.h"

ArrowPushButton::ArrowPushButton(QWidget* parent, bool upArrow) :
	QPushButton(parent),
	upArrow(upArrow)
{
	if(upArrow)
		setIcon(QIcon("Resources/arrow-up-grey.svg"));
	else
		setIcon(QIcon("Resources/arrow-down-grey.svg"));

	setStyleSheet("background-color: transparent; border-radius: 4px;");
}

void ArrowPushButton::enterEvent(QEnterEvent* event)
{
	QPushButton::enterEvent(event);
	setStyleSheet("background-color: #302c2c; border-radius: 4px;");
}

void ArrowPushButton::leaveEvent(QEvent* event)
{
	QPushButton::leaveEvent(event);
	setStyleSheet("background-color: transparent; border-radius: 4px;");
}

void ArrowPushButton::mousePressEvent(QMouseEvent* event)
{
	QPushButton::mousePressEvent(event);

	if (upArrow)
		setIcon(QIcon("Resources/arrow-up-white.svg"));
	else
		setIcon(QIcon("Resources/arrow-down-white.svg"));

	setStyleSheet("background-color: #282424; border-radius: 4px;");
}

void ArrowPushButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);

	if (upArrow)
		setIcon(QIcon("Resources/arrow-up-grey.svg"));
	else
		setIcon(QIcon("Resources/arrow-down-grey.svg"));

	setStyleSheet("background-color: #302c2c; border-radius: 4px;");
}
