#pragma once

#include <QWidget>
#include <QTime>
#include <QEvent>
#include <QTimeZone>

#include "WorldClock/ClockWidgetUI.h"

class ClockWidget : public QWidget
{
	Q_OBJECT

public:
	ClockWidget(QWidget* parent = nullptr, int id = NULL, QByteArray timeZoneId = NULL);

	void setTimeZoneId(const QByteArray& timeZoneId);
	void deleteMode(bool flag);
	void updateUI();

	int getId();
	QByteArray getTimeZoneId();

	static int lastId;

	Q_SIGNAL void deleteButtonClicked(ClockWidget* clock);

protected:
	bool event(QEvent* event) override;

private:
	void setDefaultStyle();

	Ui::ClockWidgetClass* ui;

	int id;
	QByteArray timeZoneId;
};