#include "Timer/TimerNotificationWindowUI.h"

void TimerNotificationWindowUI::setupUI(QDialog* TimerNotificationWindow)
{
	TimerNotificationWindow->setStyleSheet("background-color: #1F1F1F");

	centralLayout = new QVBoxLayout(TimerNotificationWindow);
	centralLayout->setContentsMargins(10, 10, 10, 10);
	centralLayout->setSpacing(10);

	auto descriptionLayout = new QVBoxLayout(TimerNotificationWindow);
	descriptionLayout->setContentsMargins(0, 0, 0, 0);
	descriptionLayout->setSpacing(0);

	name = new QLabel(TimerNotificationWindow);
	name->setStyleSheet("font-size: 20px; font-weight: bold;");
	name->setAlignment(Qt::AlignCenter);
	
	time = new QLabel(TimerNotificationWindow);
	time->setStyleSheet("font-size: 20px; font-weight: bold;");
	time->setAlignment(Qt::AlignCenter);

	descriptionLayout->addWidget(name);
	descriptionLayout->addWidget(time);

	centralLayout->addLayout(descriptionLayout);

	closeButton = new QPushButton("Close", TimerNotificationWindow);
	closeButton->setFixedSize(132, 32);
	closeButton->setStyleSheet(R"(
		/*QPushButton {
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
		}*/

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

	muteButton = new IconPushButton(TimerNotificationWindow, "", "transparent", "transparent", "Resources/unmuted-white.svg", "Resources/unmuted-grey.svg", "transparent", "#383838", "#343434");
	muteButton->setFixedSize(32, 32);

	unmuteButton = new IconPushButton(TimerNotificationWindow, "", "transparent", "transparent", "Resources/muted-white.svg", "Resources/muted-grey.svg", "transparent", "#383838", "#343434");
	unmuteButton->setFixedSize(32, 32);

	unmuteButton->hide();

	centralLayout->addWidget(closeButton);
}
