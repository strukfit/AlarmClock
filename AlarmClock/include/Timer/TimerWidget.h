#pragma once
#include <QWidget>
#include <QTime>
#include <QEvent>
#include <QGraphicsDropShadowEffect>

#include "TimerWidgetUI.h"

class TimerWidget : public QWidget
{
	Q_OBJECT

public:
	TimerWidget(QWidget* parent = nullptr, int id = NULL, QTime time = QTime(0, 0, 0), QString name = NULL);

	void setName(const QString& name);
	void setTime(const QTime& alarmTime);
	void updateUI();
	void deleteMode(bool flag);
	void showPlayButton();

	int getId();
	QTime getTime();
	QString getName();

	static int lastId;

signals:
	void clicked(TimerWidget* timer);
	void deleteButtonClicked(TimerWidget* timer);
	void expired(TimerWidget* timer);

protected:
	void mouseReleaseEvent(QMouseEvent* event) override;
	bool event(QEvent* event) override;

private:
	void setInactiveColors();
	void setActiveColors();
	void setDefaultStyle();

	Ui::TimerWidgetClass* ui;

	int id;
	QTime time;
	QString name;
};