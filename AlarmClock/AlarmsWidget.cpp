#include "AlarmsWidget.h"

AlarmsWidget::AlarmsWidget(QWidget* parent) :
	QWidget(parent)
{
}

void AlarmsWidget::resizeEvent(QResizeEvent* event)
{
	emit resized();
	QWidget::resizeEvent(event);
}
