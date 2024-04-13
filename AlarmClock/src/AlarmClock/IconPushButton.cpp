#include "AlarmClock/IconPushButton.h"

IconPushButton::IconPushButton(QWidget* parent, QString text, QString textColor, QString textPressedColor, QString iconPath, QString pressedIconPath, QString backgroundColor, QString hoverColor, QString pressedColor) :
	QPushButton(parent),
	textColor(textColor),
	textPressedColor(textPressedColor),
	iconPath(iconPath),
	pressedIconPath(pressedIconPath),
	backgroundColor(backgroundColor),
	hoverColor(hoverColor),
	pressedColor(pressedColor)
{
	setIcon(QIcon(iconPath));
	
	setText(text);

	setStyleSheet(QString("QPushButton { font-size: 14px; background-color: %1; color: %2; border-radius: 4px; border: 0;} QPushButton:hover { background-color: %3; } QPushButton:pressed { background-color: %4; color: %5}").arg(backgroundColor, textColor, hoverColor, pressedColor, textPressedColor));
}

IconPushButton::~IconPushButton()
{
}

void IconPushButton::mousePressEvent(QMouseEvent* event)
{
	QPushButton::mousePressEvent(event);

	setIcon(QIcon(pressedIconPath));
}

void IconPushButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);

	setIcon(QIcon(iconPath));
}
