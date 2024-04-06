#include "MainWindowUI.h"

void MainWindowUI::setupMainWindowUI(QMainWindow* MainWindowClass)
{
	centralWidget = new QWidget(MainWindowClass);
	centralWidget->setStyleSheet("background-color: #272727;");

	centralLayout = new QHBoxLayout(centralWidget);
	centralLayout->setContentsMargins(0, 0, 0, 0);
	centralLayout->setSpacing(0);

	functionSelectorWidget = new QWidget(centralWidget);
	functionSelectorWidget->setStyleSheet("background-color: white;");
	functionSelectorWidget->setFixedWidth(48);

	alarmsWidget = new AlarmsWidget(centralWidget);

	alarmsListLayout = new QVBoxLayout(alarmsWidget);
	alarmsListLayout->setContentsMargins(0, 0, 0, 0);

	alarmsListWidget = new QListWidget(alarmsWidget);
	alarmsListWidget->setSelectionMode(QAbstractItemView::NoSelection);

	alarmsListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	alarmsListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	alarmsListWidget->setStyleSheet(R"(
		QListWidget {
			
		}

		QListWidget::item { 
			background-color: #323232; 
			margin: 12px 48px 12px 48px;
		}		
		
		QListWidget::item::hover { 
			background-color: white; 
			border-radius: 5px; 
			margin: 12px 48px 12px 48px;
		}

	)");

	alarmsListLayout->addWidget(alarmsListWidget);	

	alarmsManagerWidget = new QWidget(alarmsWidget);
	alarmsManagerWidget->setStyleSheet("background-color: #2C2C2C; border: 1px solid #404040; border-radius: 10px;");

	QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
	shadowEffect->setBlurRadius(20);
	shadowEffect->setColor(QColor(0, 0, 0, 30)); 
	shadowEffect->setOffset(3, 7); 

	alarmsManagerWidget->setGraphicsEffect(shadowEffect);
	alarmsManagerWidget->setFixedSize(QSize(88, 48));

	QObject::connect(alarmsWidget, &AlarmsWidget::resized, [&] {
		alarmsManagerWidget->move(alarmsWidget->geometry().width() - alarmsManagerWidget->width() - 24, alarmsWidget->geometry().height() - alarmsManagerWidget->height() - 20);
	});

	alarmsManagerLayout = new QHBoxLayout(alarmsManagerWidget);
	alarmsManagerLayout->setContentsMargins(6, 0, 6, 0);

	deleteAlarmsButton = new IconPushButton(alarmsManagerWidget, "", "transparent", "transparent", "Resources/pen-white.svg", "Resources/pen-grey.svg", "transparent", "#383838", "#343434");
	deleteAlarmsButton->setFixedSize(QSize(36, 36));
	deleteAlarmsButton->setIconSize(QSize(20, 20));

	confirmButton = new IconPushButton(alarmsManagerWidget, "", "transparent", "transparent", "Resources/confirm-white.svg", "Resources/confirm-grey.svg", "transparent", "#383838", "#343434");
	confirmButton->setFixedSize(QSize(36, 36));
	confirmButton->setIconSize(QSize(16, 16));

	addAlarmButton = new IconPushButton(alarmsManagerWidget, "", "transparent", "transparent", "Resources/add-white.svg", "Resources/add-grey.svg", "transparent", "#383838", "#343434");
	addAlarmButton->setFixedSize(QSize(36, 36));
	addAlarmButton->setIconSize(QSize(20, 20));

	alarmsManagerLayout->addWidget(deleteAlarmsButton);
	alarmsManagerLayout->addWidget(confirmButton);
	confirmButton->hide();
	alarmsManagerLayout->addWidget(addAlarmButton);

	centralLayout->addWidget(functionSelectorWidget);
	centralLayout->addWidget(alarmsWidget);

	MainWindowClass->setLayout(centralLayout);
	MainWindowClass->setCentralWidget(centralWidget);

	QMetaObject::connectSlotsByName(MainWindowClass);
}