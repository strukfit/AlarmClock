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

class TimerNotificationWindowUI {
public:
	void setupUI(QDialog* TimerNotificationWindow);

	QVBoxLayout* centralLayout;
	QLabel* name;
	QLabel* time;
	QPushButton* closeButton;
	IconPushButton* muteButton;
	IconPushButton* unmuteButton;
};

namespace Ui {
	class TimerNotificationWindowClass : public TimerNotificationWindowUI {};
} // namespace Ui