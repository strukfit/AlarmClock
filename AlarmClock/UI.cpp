#include "UI.h"

UI::~UI()
{
	delete mainWindowCentralWidget;
	delete mainWindowSetAlarmButton;
	delete alarmsListWidget;
	delete vBoxLayout;

	delete title;
	delete setAlarmWindowVLayout;
	delete setAlarmWindowSetAlarmButton;
	delete timeSelectorHBoxLayout;
	delete timeWrapperWidget;
	delete timeSelectorWidget;
	delete hourSpinBox;
	delete minutesSpinBox;
	delete separatorLabel;
	delete editNameHBoxLayout;
	delete editSvgWidget;
	delete nameLineEdit;
	delete arrowUpButton1;
	delete arrowUpButton2;
	delete arrowDownButton1;
	delete arrowDownButton2;
	delete editNameWrapperWidget;
	delete editNameWidget;

	delete gBoxLayout;
	delete time;
	delete name;
	delete testButton;
}

int UI::defaultNameCounter = 0;

void UI::setupMainWindowUI(QMainWindow* MainWindowClass)
{
	mainWindowCentralWidget = new QWidget(MainWindowClass);

	vBoxLayout = new QVBoxLayout(mainWindowCentralWidget);
	
	alarmsListWidget = new QListWidget(mainWindowCentralWidget);

	alarmsListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	alarmsListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	alarmsListWidget->setStyleSheet(R"(
		QListWidget::item { 
			background-color: #323232; 
			border-radius: 5px; 
			margin-left: 10px; 
			margin-right: 10px; 
			margin-bottom: 5px; 
			margin-top: 5px; 
		}
	)");

	mainWindowSetAlarmButton = new QPushButton("openSetAlarmWindowButton", mainWindowCentralWidget);
	mainWindowSetAlarmButton->setObjectName("mainWindowSetAlarmButton");

	vBoxLayout->addWidget(alarmsListWidget);
	vBoxLayout->addWidget(mainWindowSetAlarmButton);

	MainWindowClass->setLayout(vBoxLayout);

	MainWindowClass->setCentralWidget(mainWindowCentralWidget);

	QMetaObject::connectSlotsByName(MainWindowClass);

}

void UI::setupSetAlarmWindowUI(QDialog* SetAlarmWindowClass)
{
	//SetAlarmWindowClass->setFixedSize(1121, 753);
	
	SetAlarmWindowClass->setStyleSheet("background-color: #201c1c;");

	setAlarmWindowVLayout = new QVBoxLayout(SetAlarmWindowClass);
	setAlarmWindowVLayout->setContentsMargins(30, 30, 30, 30);

	title = new QLabel("Add a new alarm clock");
	title->setStyleSheet("color: white; font-size: 20px; font-weight: bold;");
	setAlarmWindowVLayout->addWidget(title);

	timeWrapperWidget = new TimeWrapperWidget(SetAlarmWindowClass, "#383434", activeAccentColor);
	timeWrapperWidget->setFixedSize(272, 80);

	timeSelectorWidget = new TimeWrapperChildWidget(timeWrapperWidget, "#201c1c");
	timeSelectorWidget->setFixedSize(266, 74);

	timeSelectorWidget->move((timeWrapperWidget->width() - timeSelectorWidget->width()) / 2, (timeWrapperWidget->height() - timeSelectorWidget->height()) / 2);

	timeSelectorHBoxLayout = new QHBoxLayout(timeSelectorWidget);
	timeSelectorHBoxLayout->setContentsMargins(38, 2, 38, 2);

	hourSpinBox = new TimeSpinBox(timeSelectorWidget, 0, 23);
	hourSpinBox->setFixedSize(70, 70);
	minutesSpinBox = new TimeSpinBox(timeSelectorWidget, 0, 59);
	minutesSpinBox->setFixedSize(70, 70);

	timeSelectorHBoxLayout->addWidget(hourSpinBox);

	separatorLabel = new QLabel(timeSelectorWidget);
	separatorLabel->setText(":");
	separatorLabel->setAlignment(Qt::AlignCenter);
	separatorLabel->setStyleSheet(R"(
		color: #a8a4a4; 
		font-size: 35px; 
		font-weight: bold; 
		background-color: transparent; 
		border: none; 
	)");

	timeSelectorHBoxLayout->addWidget(separatorLabel);
	timeSelectorHBoxLayout->addWidget(minutesSpinBox);

	setAlarmWindowSetAlarmButton = new QPushButton("setAlarmButton", SetAlarmWindowClass);
	setAlarmWindowSetAlarmButton->setObjectName("setAlarmWindowSetAlarmButton");

	editNameHBoxLayout = new QHBoxLayout(SetAlarmWindowClass);

	QHBoxLayout* arrowsUpLayout = new QHBoxLayout(SetAlarmWindowClass);
	QHBoxLayout* arrowsDownLayout = new QHBoxLayout(SetAlarmWindowClass);

	arrowsUpLayout->setContentsMargins(60, 0, 60, 0);
	arrowsDownLayout->setContentsMargins(60, 0, 60, 0);

	arrowUpButton1 = new ArrowPushButton(SetAlarmWindowClass, true);
	arrowUpButton1->setFixedSize(32, 32);

	QObject::connect(arrowUpButton1, &QPushButton::pressed, [&]() {
		hourSpinBox->setValue(hourSpinBox->value() + 1);
		hourSpinBox->setFocus();
	});

	arrowUpButton2 = new ArrowPushButton(SetAlarmWindowClass, true);
	arrowUpButton2->setFixedSize(32, 32);

	QObject::connect(arrowUpButton2, &QPushButton::pressed, [&]() {
		minutesSpinBox->setValue(minutesSpinBox->value() + 1);
		minutesSpinBox->setFocus();
	});

	arrowDownButton1 = new ArrowPushButton(SetAlarmWindowClass, false);
	arrowDownButton1->setFixedSize(32, 32);

	QObject::connect(arrowDownButton1, &QPushButton::pressed, [&]() {
		hourSpinBox->setValue(hourSpinBox->value() - 1);
		hourSpinBox->setFocus();
	});

	arrowDownButton2 = new ArrowPushButton(SetAlarmWindowClass, false);
	arrowDownButton2->setFixedSize(32, 32);

	QObject::connect(arrowDownButton2, &QPushButton::pressed, [&]() {
		minutesSpinBox->setValue(minutesSpinBox->value() - 1);
		minutesSpinBox->setFocus();
	});

	arrowsUpLayout->addWidget(arrowUpButton1);
	arrowsUpLayout->addStretch(1);
	arrowsUpLayout->addWidget(arrowUpButton2);

	arrowsDownLayout->addWidget(arrowDownButton1);
	arrowsDownLayout->addStretch(1);
	arrowsDownLayout->addWidget(arrowDownButton2);

	setAlarmWindowVLayout->addLayout(arrowsUpLayout);

	setAlarmWindowVLayout->addWidget(timeWrapperWidget);

	setAlarmWindowVLayout->addLayout(arrowsDownLayout);

	editSvgWidget = new QSvgWidget(SetAlarmWindowClass);
	editSvgWidget->load(QString("Resources/edit-white.svg"));
	editSvgWidget->setFixedSize(16, 16);

	editNameHBoxLayout->addWidget(editSvgWidget);

	editNameWrapperWidget = new TimeWrapperWidget(SetAlarmWindowClass, "#383434", activeAccentColor, false);
	editNameWrapperWidget->setFixedSize(247, 34);

	editNameWidget = new TimeWrapperChildWidget(editNameWrapperWidget, "#201c1c");
	editNameWidget->setFixedSize(243, 30);

	editNameWidget->move(2, 1);

	nameLineEditLayout = new QHBoxLayout(editNameWidget);
	nameLineEditLayout->setContentsMargins(0, 1, 2, 0);

	nameLineEdit = new NameLineEdit(editNameWidget);
	nameLineEdit->setFixedSize(243, 28);

	nameLineEdit->setStyleSheet(R"(
        color: white;
        font-size: 14px;
        background-color: transparent; 
        border: 0; 
		margin-left: 9px;
		margin-right: 35px;
		margin-bottom: 1px;
    )");
	
	nameLineEdit->setPlaceholderText("Alarm clock name");
	nameLineEdit->setText(defaultName + " (" + QString::number(defaultNameCounter + 1) + ")");

	xButton = new XPushButton(editNameWidget);
	xButton->setFixedSize(29, 25);
	xButton->hide();
	
	QObject::connect(nameLineEdit, &NameLineEdit::focusGained, [&] {
		if(!nameLineEdit->text().isEmpty())
			xButton->show();
	});

	QObject::connect(nameLineEdit, &NameLineEdit::focusLost, [&] {
		xButton->hide();
	});

	QObject::connect(nameLineEdit, &NameLineEdit::textChanged, [&] {
		if(!nameLineEdit->text().isEmpty())
			xButton->show();
		else 
			xButton->hide();
	});

	QObject::connect(xButton, &QPushButton::pressed, [&] {
		if (!nameLineEdit->text().isEmpty())
			nameLineEdit->clear();
		nameLineEdit->setFocus();
	});

	nameLineEditLayout->addWidget(nameLineEdit);
	nameLineEditLayout->addStretch(1);
	nameLineEditLayout->addWidget(xButton);

	editNameHBoxLayout->addWidget(editNameWrapperWidget);

	setAlarmWindowVLayout->addLayout(editNameHBoxLayout);

	QObject::connect(setAlarmWindowSetAlarmButton, &QPushButton::pressed, [&] {
		if (nameLineEdit->text() == (defaultName + " (" + QString::number(defaultNameCounter + 1) + ")"))
			defaultNameCounter++;
	});

	setAlarmWindowVLayout->addWidget(setAlarmWindowSetAlarmButton);

	SetAlarmWindowClass->setLayout(setAlarmWindowVLayout);

	QMetaObject::connectSlotsByName(SetAlarmWindowClass);
}

void UI::setupAlarmClockWidgetUI(QWidget* AlarmClockWidgetClass)
{
	gBoxLayout = new QGridLayout(AlarmClockWidgetClass);

	time = new QLabel(AlarmClockWidgetClass);
	time->setStyleSheet("color: white; font-size: 50px; font-weight: bold;");

	name = new QLabel(AlarmClockWidgetClass);
	name->setStyleSheet("color: white; font-size: 20px ");

	testButton = new QPushButton("test", AlarmClockWidgetClass);

	gBoxLayout->addWidget(time, 0, 0);
	gBoxLayout->addWidget(name, 1, 0);
	gBoxLayout->addWidget(testButton, 0, 1);

	AlarmClockWidgetClass->setLayout(gBoxLayout);

	QMetaObject::connectSlotsByName(AlarmClockWidgetClass);
}
