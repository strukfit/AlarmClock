#pragma once

#include <QPushButton>
#include <QEvent>

class ArrowPushButton : public QPushButton
{
public:
	ArrowPushButton(QWidget* parent = nullptr, bool upArrow = true);

protected:
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	bool upArrow;
};