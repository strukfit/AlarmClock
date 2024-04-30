#pragma once

#include <QDialog>
#include <QBOXLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSvgWidget>
#include <QAbstractItemView>
#include <QStyledItemDelegate>

#include <IconPushButton.h>

class AlarmNotificationWindowUI {
public:
	void setupUI(QDialog* AlarmNotificationWindow);

	QVBoxLayout* centralLayout;
	QVBoxLayout* descriptionLayout;
	QLabel* name;
	QLabel* time;
	QHBoxLayout* snoozeComboBoxLayout;
	QSvgWidget* snoozeSvgWidget;
	QComboBox* snoozeComboBox;
	QHBoxLayout* buttonsLayout;
	QPushButton* snoozeButton;
	QPushButton* closeButton;
	IconPushButton* muteButton;
	IconPushButton* unmuteButton;
};

namespace Ui {
	class AlarmNotificationWindowClass : public AlarmNotificationWindowUI {};
} // namespace Ui