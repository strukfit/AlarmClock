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

	void setActive(bool flag);
	void setName(const QString& name);
	void setTime(const QTime& alarmTime);
	void updateUI();
	void setInactiveColors();
	void setActiveColors();
	void deleteMode(bool flag);
	void setNotificationOpen(bool flag);

	int getId();
	QTime getTime();
	QString getName();
	bool isActive();
	bool isNotifficationOpen();

	static int lastId;

signals:
	void clicked(TimerWidget* alarm);
	void deleteButtonClicked(TimerWidget* alarm);

protected:
	void mouseReleaseEvent(QMouseEvent* event) override;
	bool event(QEvent* event) override;

private:
	void setDefaultStyle();

	Ui::TimerWidgetClass* ui;

	int id;
	QTime time;
	QString name;

	bool notifficationOpen;
};