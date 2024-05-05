#include "Timer/TimerWidgetUI.h"

void TimerWidgetUI::setupUI(QWidget* TimerWidget)
{
	TimerWidget->setContentsMargins(0, 0, 0, 0);
	TimerWidget->setFixedHeight(324);
	TimerWidget->setAttribute(Qt::WA_StyledBackground, true);

	layout = new QVBoxLayout(TimerWidget);
	layout->setContentsMargins(15, 11, 3, 21);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignCenter);

	name = new QLabel(TimerWidget);
	name->setStyleSheet("background-color: transparent; color: white; font-size: 14px; font-weight: bold; border: 0;");

	deleteButton = new IconPushButton(TimerWidget, "", "transparent", "transparent", "Resources/delete-grey.svg", "Resources/delete-grey.svg", "transparent", "#424242", "#363636");
	deleteButton->setFixedSize(QSize(32, 32));
	deleteButton->setIconSize(QSize(16, 16));

	deleteButton->hide();
	
	auto hLayout = new QHBoxLayout(TimerWidget);
	hLayout->addWidget(name);

	layout->addLayout(hLayout);
	
	auto pLayout = new QHBoxLayout(TimerWidget);

	progressBar = new CircularProgressBar(TimerWidget, 0);
	progressBar->setFixedSize(230, 230);
	
	pLayout->addStretch();
	pLayout->addWidget(progressBar);
	pLayout->addStretch();

	layout->addLayout(pLayout);
	layout->addStretch();

	auto manageButtons = new QHBoxLayout(TimerWidget);
	manageButtons->setContentsMargins(0, 0, 0, 0);
	manageButtons->setSpacing(13);

	playButton = new IconPushButton(TimerWidget, "", "", "", "Resources/play-black.svg", "Resources/play-light.svg", "#76B9ED", "#6FABDA", "#679DC6", 15, "Resources/play-inactive.svg");
	playButton->setFixedSize(QSize(30, 30));
	playButton->setIconSize(QSize(13, 13));
	playButton->setStyleSheet(playButton->styleSheet().append(R"(
		QPushButton:disabled {
			background-color: #525252;
		}
	)"));
	
	manageButtons->addStretch();
	manageButtons->addWidget(playButton);

	pauseButton = new IconPushButton(TimerWidget, "", "", "", "Resources/pause-black.svg", "Resources/pause-light.svg", "#76B9ED", "#6FABDA", "#679DC6", 15, "Resources/pause-inactive.svg");
	pauseButton->setFixedSize(QSize(30, 30));
	pauseButton->setIconSize(QSize(13, 13));
	pauseButton->setStyleSheet(playButton->styleSheet().append(R"(
		QPushButton:disabled {
			background-color: #525252;
		}
	)"));
	pauseButton->hide();

	manageButtons->addWidget(pauseButton);

	restartButton = new IconPushButton(TimerWidget, "", "", "", "Resources/restart-white.svg", "Resources/restart-grey.svg", "#3B3B3B", "#3b3b3b", "#363636", 15, "Resources/restart-inactive.svg");
	restartButton->setFixedSize(QSize(30, 30));
	restartButton->setIconSize(QSize(20, 20));
	restartButton->setStyleSheet(restartButton->styleSheet().append("QPushButton { border: 1px solid #474747; }")); 

	manageButtons->addWidget(restartButton);
	manageButtons->addStretch();

	layout->addLayout(manageButtons);

	QMetaObject::connectSlotsByName(TimerWidget);
}