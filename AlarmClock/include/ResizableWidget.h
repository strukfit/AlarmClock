#pragma once

#include <QWidget>

class ResizableWidget : public QWidget
{
	Q_OBJECT

signals:
	void resized();

public:
	ResizableWidget(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;
};