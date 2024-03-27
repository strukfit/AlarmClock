#pragma once

#include <QLabel>
#include <QBoxLayout>
#include <QSvgWidget>
#include <QtSvg/QSvgRenderer>

#include "TimeSpinBox.h"
#include "TimeWrapperWidget.h"
#include "ArrowPushButton.h"
#include "NameLineEdit.h"
#include "XPushButton.h"
#include "IconPushButton.h"

class AlarmWindowUI
{
public:
	~AlarmWindowUI();

	void setupAddAlarmWindowUI(QDialog* SetAlarmWindowClass);
	void setupEditAlarmWindowUI(QDialog* SetAlarmWindowClass);
	void setDefaultTime();
	void setDefaultName();

	QLabel* title;
	QVBoxLayout* setAlarmWindowVLayout;
	QHBoxLayout* timeSelectorHBoxLayout;
	TimeWrapperWidget* timeWrapperWidget;
	TimeWrapperChildWidget* timeSelectorWidget;
	TimeSpinBox* hoursSpinBox;
	TimeSpinBox* minutesSpinBox;
	QLabel* separatorLabel;
	QHBoxLayout* editNameHBoxLayout;
	QSvgWidget* editSvgWidget;
	NameLineEdit* nameLineEdit;
	ArrowPushButton* arrowUpButton1;
	ArrowPushButton* arrowUpButton2;
	ArrowPushButton* arrowDownButton1;
	ArrowPushButton* arrowDownButton2;
	TimeWrapperWidget* editNameWrapperWidget;
	TimeWrapperChildWidget* editNameWidget;
	QHBoxLayout* nameLineEditLayout;
	XPushButton* xButton;
	IconPushButton* setAlarmButton;
	IconPushButton* cancelButton;
	QHBoxLayout* saveCancelLayout;

	static int defaultNameCounter;

private:
	const QString activeAccentColor = "#78bcec";
	const QString inactiveAccentColor = "#9c9c9c";

	QString defaultName = "Alarm clock";
};

namespace Ui {
	class SetAlarmWindowClass : public AlarmWindowUI{};
} // namespace Ui