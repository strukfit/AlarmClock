#pragma once

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class TimeWrapperWidget : public QWidget
{
	Q_OBJECT

public:
	TimeWrapperWidget(QWidget* parent = nullptr, QString backgroundColor = "#000", QString accentColor = "#000", bool isTimeSelector = true);
	~TimeWrapperWidget();
	
	void childFocusIn();
	void childFocusOut();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QString backgroundColor, activeAccentColor, inactiveAccentColor = "#9c9c9c";
	bool childHasFocus, isTimeSelector;
};

class TimeWrapperChildWidget : public QWidget
{
	Q_OBJECT

public:
	TimeWrapperChildWidget(QWidget* parent = nullptr, QString backgroundColor = "#000");
	~TimeWrapperChildWidget();

	void childFocusIn();
	void childFocusOut();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QString backgroundColor;
	bool childHasFocus;
};