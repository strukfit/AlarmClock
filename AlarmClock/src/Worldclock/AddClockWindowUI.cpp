#include "Worldclock/AddClockWindowUI.h"

void AddClockWindowUI::setupUI(QDialog* AddClockWindow)
{
	AddClockWindow->setStyleSheet("background-color: #201c1c; border: none;");

	auto layout = new QVBoxLayout(AddClockWindow);
	layout->setContentsMargins(30, 30, 30, 30);
	layout->setSpacing(0);

	auto title = new QLabel("Add a new location");
	title->setStyleSheet("color: white; font-size: 20px; font-weight: bold;");
	layout->addWidget(title);

	layout->addSpacing(24);

	locationSearchBar = new LocationSearchBar(AddClockWindow);
	layout->addWidget(locationSearchBar);

	layout->addSpacing(48);

	auto buttonsLayout = new QHBoxLayout(AddClockWindow);
	buttonsLayout->setSpacing(10);

	addButton = new IconPushButton(AddClockWindow, "Add", "#07080a", "#37516a", "Resources/add-dark.svg", "Resources/add-light.svg", "#78bcec", "#70acdc", "#689cc4");
	addButton->setFixedHeight(32);
	addButton->setIconSize(QSize(18, 18));
	buttonsLayout->addWidget(addButton);

	cancelButton = new IconPushButton(AddClockWindow, "Cancel", "white", "#a09c9c", "Resources/x-white.svg", "Resources/x-grey.svg", "#292929", "#2F2F2F", "#232323");
	cancelButton->setFixedHeight(32);
	cancelButton->setIconSize(QSize(18, 18));
	buttonsLayout->addWidget(cancelButton);

	layout->addLayout(buttonsLayout);
}
