#include "ResizableWidget.h"

ResizableWidget::ResizableWidget(QWidget* parent) :
	QWidget(parent)
{
}

void ResizableWidget::resizeEvent(QResizeEvent* event)
{
	emit resized();
	QWidget::resizeEvent(event);
}
