#pragma once

#include <QScrollBar>
#include <QEvent>
#include <QTimer>
#include <QPropertyAnimation>

class CustomScrollBar : public QScrollBar
{
public:
	CustomScrollBar(QWidget* parent = nullptr);

protected:
	bool event(QEvent* event) override;

private:
	void setDefaultStyle();
};