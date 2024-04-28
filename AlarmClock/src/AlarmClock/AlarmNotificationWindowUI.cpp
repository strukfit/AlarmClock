#include "AlarmClock/AlarmNotificationWindowUI.h"

void AlarmNotificationWindowUI::setupUI(QDialog* AlarmNotificationWindow)
{
	AlarmNotificationWindow->setStyleSheet("background-color: #1F1F1F");

	centralLayout = new QVBoxLayout(AlarmNotificationWindow);
	centralLayout->setContentsMargins(10, 10, 10, 10);
	centralLayout->setSpacing(10);

	descriptionLayout = new QVBoxLayout(AlarmNotificationWindow);
	descriptionLayout->setContentsMargins(0, 0, 0, 0);
	descriptionLayout->setSpacing(0);
	descriptionLayout->setAlignment(Qt::AlignCenter);

	name = new QLabel(AlarmNotificationWindow);
	name->setStyleSheet("font-size: 20px; font-weight: bold;");
	name->setAlignment(Qt::AlignCenter);

	time = new QLabel(AlarmNotificationWindow);
	time->setStyleSheet("font-size: 60px; font-weight: bold;");
	time->setAlignment(Qt::AlignCenter);

	descriptionLayout->addWidget(name);
	descriptionLayout->addWidget(time);

	centralLayout->addLayout(descriptionLayout);

	snoozeComboBoxLayout = new QHBoxLayout(AlarmNotificationWindow);
	snoozeComboBoxLayout->setContentsMargins(0, 0, 0, 0);
	snoozeComboBoxLayout->setSpacing(7);

	snoozeSvgWidget = new QSvgWidget(AlarmNotificationWindow);
	snoozeSvgWidget->load(QString("Resources/snooze-white.svg"));
	snoozeSvgWidget->setFixedSize(22, 20);
	
	snoozeComboBox = new QComboBox(AlarmNotificationWindow);
	snoozeComboBox->setFixedSize(245, 32);
	//snoozeComboBox->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	//snoozeComboBox->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
	QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
	snoozeComboBox->setItemDelegate(itemDelegate);
	snoozeComboBox->setStyleSheet(R"(
		QComboBox {
			background-color: #292929;
			color: white; 
			font-size: 14px;
			border: 1px solid #313131; 
			border-radius: 4px;
			padding-left: 12px;
		}

		QComboBox:hover {
			background-color: #2F2F2F; 
			color: white; 
			font-size: 14px;
			border: 1px solid #2F2F2F; 
			border-radius: 4px;
		}

		QComboBox::drop-down:button {
			background-color: transparent;
		}
		
		QComboBox::down-arrow {
			image: url(Resources/arrow-down-white.svg);
			width: 14px;
			height: 9px;
			margin-right: 26px;
		}

		QComboBox QAbstractItemView {
			background-color: #2C2C2C;
			selection-background-color: #383838;
			outline: 0px;
			border: 0;
			/*border-radius: 10px;*/
			/*padding: 12px;*/
			
		}

		QComboBox QAbstractItemView::item {
			min-height: 32px;
		}
	)");

	snoozeComboBoxLayout->addWidget(snoozeSvgWidget);
	snoozeComboBoxLayout->addWidget(snoozeComboBox);

	centralLayout->addLayout(snoozeComboBoxLayout);

	buttonsLayout = new QHBoxLayout(AlarmNotificationWindow);
	buttonsLayout->setContentsMargins(0, 0, 0, 0);

	snoozeButton = new QPushButton("Snooze", AlarmNotificationWindow);
	snoozeButton->setFixedSize(132, 32);
	snoozeButton->setStyleSheet(R"(
		QPushButton {
			background-color: #292929;
			color: white;
			font-size: 14px;
			border-radius: 4px; 
			border: 0;
		}
		
		QPushButton:hover {
			background-color: #2F2F2F;
			color: white;
			font-size: 14px;
			border-radius: 4px; 
			border: 0;
		}

		QPushButton:pressed {
			background-color: #232323;
			color: #a09c9c;
			font-size: 14px;
			border-radius: 4px; 
			border: 0;
		}
	)");

	closeButton = new QPushButton("Close", AlarmNotificationWindow);
	closeButton->setFixedSize(132, 32);
	closeButton->setStyleSheet(R"(
		QPushButton {
			background-color: #292929;
			color: white;
			font-size: 14px;
			border-radius: 4px; 
			border: 0;
		}
		
		QPushButton:hover {
			background-color: #2F2F2F;
			color: white;
			font-size: 14px;
			border-radius: 4px; 
			border: 0;
		}
		
		QPushButton:pressed {
			background-color: #232323;
			color: #a09c9c;
			font-size: 14px;
			border-radius: 4px; 
			border: 0;
		}
	)");

	buttonsLayout->addWidget(snoozeButton);
	buttonsLayout->addWidget(closeButton);

	muteButton = new IconPushButton(AlarmNotificationWindow, "", "transparent", "transparent", "Resources/unmuted-white.svg", "Resources/unmuted-grey.svg", "transparent", "#383838", "#343434");
	muteButton->setFixedSize(32, 32);

	unmuteButton = new IconPushButton(AlarmNotificationWindow, "", "transparent", "transparent", "Resources/muted-white.svg", "Resources/muted-grey.svg", "transparent", "#383838", "#343434");
	unmuteButton->setFixedSize(32, 32);

	unmuteButton->hide();

	centralLayout->addLayout(buttonsLayout);
}
