#include "XPushButton.h"

XPushButton::XPushButton(QWidget* parent) :
	QPushButton(parent)
{
	setIcon(QIcon("Resources/x-grey.svg"));

	setStyleSheet("background-color: transparent; border-radius: 4px;");
}

void XPushButton::enterEvent(QEnterEvent* event)
{
	QPushButton::enterEvent(event);
	setStyleSheet("background-color: #302c2c; border-radius: 4px;");
}

void XPushButton::leaveEvent(QEvent* event)
{
	QPushButton::leaveEvent(event);
	setStyleSheet("background-color: transparent; border-radius: 4px;");
}

void XPushButton::mousePressEvent(QMouseEvent* event)
{
	QPushButton::mousePressEvent(event);

	setIcon(QIcon("Resources/x-white.svg"));

	setStyleSheet("background-color: #282424; border-radius: 4px;");
}

void XPushButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);

	setIcon(QIcon("Resources/x-grey.svg"));

	setStyleSheet("background-color: #302c2c; border-radius: 4px;");
}
