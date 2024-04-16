#pragma once
#include <QWidget>
#include <QTime>
#include <QModelIndex>
#include <QMessageBox>
#include "AlarmClockWidgetUI.h"

class AlarmClockWidget : public QWidget
{
	Q_OBJECT

public:
	AlarmClockWidget(QWidget* parent = nullptr, int id = NULL, QTime time = QTime(0, 0), QString name = NULL);

	void setActive(bool flag);
	void setName(const QString& name);
	void setAlarmTime(const QTime& alarmTime);
	void updateUI();
	void setModelIndex(const QModelIndex& modelIndex);
	void setInactiveColors();
	void setActiveColors();
	void deleteMode(bool flag);
	void setRemainingTime(QString time);

	int getId();
	QTime getAlarmTime();
	QString getName();
	bool isActive();
	QModelIndex getModelIndex();

	static int lastId;

signals:
	void clicked(AlarmClockWidget* alarm);
	void deleteButtonClicked(AlarmClockWidget* alarm);

protected:
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	Ui::AlarmClockWidgetClass* ui;

	int id;
	QTime alarmTime;
	QString name;

	QModelIndex modelIndex;
};