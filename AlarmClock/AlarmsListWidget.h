#pragma once

#include <QListWidget>
#include <QMouseEvent>
#include <QMessageBox>

class AlarmsListWidget : public QListWidget
{
public:
	AlarmsListWidget(QWidget* parent = nullptr);

protected: 
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	//void enterEvent(QEnterEvent* event) override;
};