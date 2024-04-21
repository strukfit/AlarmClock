#pragma once

#include <QScrollBar>
#include <QEvent>
#include <QTimer>
#include <QPropertyAnimation>

class AlarmScrollBar : public QScrollBar
{
public:
	AlarmScrollBar(QWidget* parent = nullptr);

protected:
	bool event(QEvent* event) override;

private:
	void setDefaultStyle();
};