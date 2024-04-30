#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QSvgWidget>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionButton>

class CheckableButton : public QPushButton
{
	Q_OBJECT

public:
	CheckableButton(QWidget* parent = nullptr, QString text = "", QString textColor = "#000", QString textPressedColor = "#000", QString iconPath = "", QString pressedIconPath = "", QString backgroundColor = "#000", QString hoverColor = "#000", QString pressedColor = "#000");

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	QString iconPath;
	QString pressedIconPath;

	QSvgWidget* indicatorIcon;
};