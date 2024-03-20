#include "TimeWrapperWidget.h"

TimeWrapperWidget::TimeWrapperWidget(QWidget* parent, QString backgroundColor, QString accentColor, bool isTimeSelector) :
	QWidget(parent),
	backgroundColor(backgroundColor),
	activeAccentColor(accentColor),
	childHasFocus(false),
	isTimeSelector(isTimeSelector)
{
}

TimeWrapperWidget::~TimeWrapperWidget()
{
}

void TimeWrapperWidget::paintEvent(QPaintEvent* event)
{
	int stripHeight = 2;

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRectF wrappedRect;
	if(isTimeSelector)
		wrappedRect = QRectF(1, 1, width() - 2, height() - 1);
	else
		wrappedRect = QRectF(0, 2, width(), height() - 3);

	painter.setPen(Qt::NoPen);

	if(childHasFocus)
		painter.setBrush(QColor(activeAccentColor));
	else
		painter.setBrush(QColor(inactiveAccentColor));

	painter.drawRoundedRect(wrappedRect, 5, 5);

	painter.setBrush(QColor(backgroundColor));

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRoundedRect(QRect(0, 0, width(), height() - stripHeight * 1.75), 5, 5);
	path.addRoundedRect(QRect(0, height() - stripHeight * 5, width(), stripHeight * 3.5), 1, 1);
	painter.drawPath(path.simplified());
}

void TimeWrapperWidget::childFocusIn()
{
	childHasFocus = true;
	update();
}

void TimeWrapperWidget::childFocusOut()
{
	childHasFocus = false;
	update();
}

TimeWrapperChildWidget::TimeWrapperChildWidget(QWidget* parent, QString backgroundColor) :
	QWidget(parent),
	backgroundColor(backgroundColor),
	childHasFocus(false)
{
}

TimeWrapperChildWidget::~TimeWrapperChildWidget()
{
}

void TimeWrapperChildWidget::paintEvent(QPaintEvent* event)
{
	if (childHasFocus)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(backgroundColor));
		painter.drawRoundedRect(rect(), 3, 3);
	}
}

void TimeWrapperChildWidget::childFocusIn()
{
	childHasFocus = true;
	update();
}

void TimeWrapperChildWidget::childFocusOut()
{
	childHasFocus = false;
	update();
}
