#include "XPushButton.h"

XPushButton::XPushButton(QWidget* parent) :
	QPushButton(parent)
{
	setIcon(QIcon("Resources/x-grey.svg"));

	setStyleSheet(" QPushButton { background-color: transparent; border-radius: 4px; } QPushButton:hover { background-color: #302c2c; } QPushButton:pressed { background-color: #282424; }");
}

void XPushButton::mousePressEvent(QMouseEvent* event)
{
	QPushButton::mousePressEvent(event);

	setIcon(QIcon("Resources/x-white.svg"));
}

void XPushButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);

	setIcon(QIcon("Resources/x-grey.svg"));
}
