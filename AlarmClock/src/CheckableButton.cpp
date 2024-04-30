#include "CheckableButton.h"

CheckableButton::CheckableButton(QWidget* parent, QString text, QString textColor, QString textPressedColor, QString iconPath, QString pressedIconPath, QString backgroundColor, QString hoverColor, QString pressedColor):
	QPushButton(parent),
	iconPath(iconPath),
	pressedIconPath(pressedIconPath)
{
	auto layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignLeft);

	indicatorIcon = new QSvgWidget(this);
	indicatorIcon->load(QString("Resources/indicator.svg"));
	indicatorIcon->setFixedSize(3, height()/2);
	indicatorIcon->hide();

	layout->addWidget(indicatorIcon);

	setIcon(QIcon(iconPath));

	setText(text);
	
	setCheckable(true);
	setAutoExclusive(true);

	setStyleSheet(QString(R"(
		QPushButton { 
			font-size: 14px; 
			background-color: %1; 
			color: %2; 
			border-radius: 4px; 
			border: 0;		
		} 
		
		QPushButton:hover { 
			background-color: %3; 
		} 
		
		QPushButton:pressed { 
			background-color: %4; 
			color: %5
		}

		QPushButton:checked { 
			background-color: %3; 
			color: %2;
		}

		QPushButton:checked:pressed { 
			background-color: %3; 
			color: %5;
		}
	)").arg(backgroundColor, textColor, hoverColor, pressedColor, textPressedColor));

	layout->addWidget(this);

	setLayout(layout);

	connect(this, &QPushButton::toggled, [&](bool checked) {
		if(checked)
			this->indicatorIcon->show();
		else
			this->indicatorIcon->hide();
	});
}

void CheckableButton::mousePressEvent(QMouseEvent* event)
{
	QPushButton::mousePressEvent(event);

	setIcon(QIcon(pressedIconPath));
}

void CheckableButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);

	setIcon(QIcon(iconPath));
}
