#pragma once

#include <QPushButton>

class XPushButton : public QPushButton
{
public:
	XPushButton(QWidget* parent = nullptr);

protected:
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
};