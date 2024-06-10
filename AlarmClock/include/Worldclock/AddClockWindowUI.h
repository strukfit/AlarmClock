#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "LocationSearchBar.h"
#include "IconPushButton.h"

class AddClockWindowUI 
{
public:
	void setupUI(QDialog* AddClockWindow);

	LocationSearchBar* locationSearchBar;
	IconPushButton* addButton;
	IconPushButton* cancelButton;
};

namespace Ui {
	class AddClockWindowClass : public AddClockWindowUI {};
} // namespace Ui