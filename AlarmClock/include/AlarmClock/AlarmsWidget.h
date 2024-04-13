#pragma once

#include <QWidget>

class AlarmsWidget : public QWidget
{
	Q_OBJECT

signals:
	void resized();

public:
	AlarmsWidget(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;
};