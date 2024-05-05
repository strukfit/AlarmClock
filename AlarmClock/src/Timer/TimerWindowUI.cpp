#include "Timer/TimerWindowUI.h"

void TimerWindowUI::setupAddTimerWindowUI(QDialog* TimerWindowClass)
{
	TimerWindowClass->setStyleSheet("background-color: #201c1c; border: none;");

	setTimerWindowVLayout = new QVBoxLayout(TimerWindowClass);
	setTimerWindowVLayout->setContentsMargins(30, 30, 30, 30);

	title = new QLabel("Add a new timer");
	title->setStyleSheet("color: white; font-size: 20px; font-weight: bold;");

	setTimerWindowVLayout->addWidget(title);

	timeWrapperWidget = new TimeWrapperWidget(TimerWindowClass, "#383434", activeAccentColor);
	timeWrapperWidget->setFixedSize(272, 80);

	timeSelectorWidget = new TimeWrapperChildWidget(timeWrapperWidget, "#201c1c", "transparent");
	timeSelectorWidget->setFixedSize(266, 74);

	timeSelectorWidget->move((timeWrapperWidget->width() - timeSelectorWidget->width()) / 2, (timeWrapperWidget->height() - timeSelectorWidget->height()) / 2);

	timeSelectorHBoxLayout = new QHBoxLayout(timeSelectorWidget);
	timeSelectorHBoxLayout->setContentsMargins(2, 2, 2, 2);

	hoursSpinBox = new TimeSpinBox(timeSelectorWidget, 0, 23);
	hoursSpinBox->setFixedSize(70, 70);
	minutesSpinBox = new TimeSpinBox(timeSelectorWidget, 0, 59);
	minutesSpinBox->setFixedSize(70, 70);
	secondsSpinBox = new TimeSpinBox(timeSelectorWidget, 0, 59);
	secondsSpinBox->setFixedSize(70, 70);

	hoursSpinBox->setValue(0);
	minutesSpinBox->setValue(0);
	secondsSpinBox->setValue(0);

	timeSelectorHBoxLayout->addWidget(hoursSpinBox);

	auto separatorLabel = new QLabel(timeSelectorWidget);
	separatorLabel->setText(":");
	separatorLabel->setAlignment(Qt::AlignCenter);
	separatorLabel->setStyleSheet(R"(
		color: #a8a4a4; 
		font-size: 35px; 
		font-weight: bold; 
		background-color: transparent; 
		border: none; 
	)");

	auto separatorLabel2 = new QLabel(timeSelectorWidget);
	separatorLabel2->setText(":");
	separatorLabel2->setAlignment(Qt::AlignCenter);
	separatorLabel2->setStyleSheet(R"(
		color: #a8a4a4; 
		font-size: 35px; 
		font-weight: bold; 
		background-color: transparent; 
		border: none; 
	)");

	timeSelectorHBoxLayout->addWidget(separatorLabel);
	timeSelectorHBoxLayout->addWidget(minutesSpinBox);
	timeSelectorHBoxLayout->addWidget(separatorLabel2);
	timeSelectorHBoxLayout->addWidget(secondsSpinBox);

	editNameHBoxLayout = new QHBoxLayout(TimerWindowClass);

	QHBoxLayout* arrowsUpLayout = new QHBoxLayout(TimerWindowClass);
	QHBoxLayout* arrowsDownLayout = new QHBoxLayout(TimerWindowClass);

	arrowsUpLayout->setContentsMargins(24, 0, 24, 0);
	arrowsDownLayout->setContentsMargins(24, 0, 24, 0);

	arrowUpButton1 = new ArrowPushButton(TimerWindowClass, true);
	arrowUpButton1->setFixedSize(32, 32);

	QObject::connect(arrowUpButton1, &QPushButton::pressed, [&]() {
		hoursSpinBox->setValue(hoursSpinBox->value() + 1);
		hoursSpinBox->setFocus();
	});

	arrowUpButton2 = new ArrowPushButton(TimerWindowClass, true);
	arrowUpButton2->setFixedSize(32, 32);

	QObject::connect(arrowUpButton2, &QPushButton::pressed, [&]() {
		minutesSpinBox->setValue(minutesSpinBox->value() + 1);
		minutesSpinBox->setFocus();
		});

	arrowUpButton3 = new ArrowPushButton(TimerWindowClass, true);
	arrowUpButton3->setFixedSize(32, 32);

	QObject::connect(arrowUpButton3, &QPushButton::pressed, [&]() {
		secondsSpinBox->setValue(secondsSpinBox->value() + 1);
		secondsSpinBox->setFocus();
	});

	arrowDownButton1 = new ArrowPushButton(TimerWindowClass, false);
	arrowDownButton1->setFixedSize(32, 32);

	QObject::connect(arrowDownButton1, &QPushButton::pressed, [&]() {
		hoursSpinBox->setValue(hoursSpinBox->value() - 1);
		hoursSpinBox->setFocus();
		});

	arrowDownButton2 = new ArrowPushButton(TimerWindowClass, false);
	arrowDownButton2->setFixedSize(32, 32);

	QObject::connect(arrowDownButton2, &QPushButton::pressed, [&]() {
		minutesSpinBox->setValue(minutesSpinBox->value() - 1);
		minutesSpinBox->setFocus();
		});

	arrowDownButton3 = new ArrowPushButton(TimerWindowClass, false);
	arrowDownButton3->setFixedSize(32, 32);

	QObject::connect(arrowDownButton3, &QPushButton::pressed, [&]() {
		secondsSpinBox->setValue(secondsSpinBox->value() - 1);
		secondsSpinBox->setFocus();
	});

	arrowsUpLayout->addWidget(arrowUpButton1);
	arrowsUpLayout->addStretch(1);
	arrowsUpLayout->addWidget(arrowUpButton2);
	arrowsUpLayout->addStretch(1);
	arrowsUpLayout->addWidget(arrowUpButton3);

	arrowsDownLayout->addWidget(arrowDownButton1);
	arrowsDownLayout->addStretch(1);
	arrowsDownLayout->addWidget(arrowDownButton2);
	arrowsDownLayout->addStretch(1);
	arrowsDownLayout->addWidget(arrowDownButton3);

	QVBoxLayout* timeSelectorLayout = new QVBoxLayout(TimerWindowClass);

	setTimerWindowVLayout->addSpacing(13);

	setTimerWindowVLayout->addLayout(arrowsUpLayout);
	setTimerWindowVLayout->addWidget(timeWrapperWidget);
	setTimerWindowVLayout->addLayout(arrowsDownLayout);

	editSvgWidget = new QSvgWidget(TimerWindowClass);
	editSvgWidget->load(QString("Resources/edit-white.svg"));
	editSvgWidget->setFixedSize(16, 16);

	editNameHBoxLayout->addWidget(editSvgWidget);

	editNameWrapperWidget = new TimeWrapperWidget(TimerWindowClass, "#383434", activeAccentColor, false);
	editNameWrapperWidget->setFixedSize(247, 34);

	editNameWidget = new TimeWrapperChildWidget(editNameWrapperWidget, "#292929", "#2F2F2F");
	editNameWidget->setFixedSize(243, 30);

	editNameWidget->move(2, 1);

	nameLineEditLayout = new QHBoxLayout(editNameWidget);
	nameLineEditLayout->setContentsMargins(0, 1, 2, 0);

	nameLineEdit = new NameLineEdit(editNameWidget);
	nameLineEdit->setText(defaultName);
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

	xButton = new IconPushButton(editNameWidget, "", "", "", "Resources/x-grey.svg", "Resources/x-white.svg", "transparent", "#302c2c", "#282424");
	xButton->setFixedSize(29, 25);
	xButton->hide();

	QObject::connect(nameLineEdit, &NameLineEdit::focusGained, [&] {
		if (!nameLineEdit->text().isEmpty())
			xButton->show();
		});

	QObject::connect(nameLineEdit, &NameLineEdit::focusLost, [&] {
		xButton->hide();
		});

	QObject::connect(nameLineEdit, &NameLineEdit::textChanged, [&] {
		if (!nameLineEdit->text().isEmpty())
			xButton->show();
		else
			xButton->hide();
		});

	QObject::connect(xButton, &QPushButton::clicked, [&] {
		if (!nameLineEdit->text().isEmpty())
			nameLineEdit->clear();
		nameLineEdit->setFocus();
		});

	nameLineEditLayout->addWidget(nameLineEdit);
	nameLineEditLayout->addStretch(1);
	nameLineEditLayout->addWidget(xButton);

	editNameHBoxLayout->addWidget(editNameWrapperWidget);

	setTimerWindowVLayout->addSpacing(14);

	setTimerWindowVLayout->addLayout(editNameHBoxLayout);

	saveCancelLayout = new QHBoxLayout(TimerWindowClass);

	setTimerButton = new IconPushButton(TimerWindowClass, "Save", "#07080a", "#37516a", "Resources/save-dark.svg", "Resources/save-light.svg", "#78bcec", "#70acdc", "#689cc4");
	setTimerButton->setFixedHeight(32);
	setTimerButton->setIconSize(QSize(18, 18));

	cancelButton = new IconPushButton(TimerWindowClass, "Cancel", "white", "#a09c9c", "Resources/x-white.svg", "Resources/x-grey.svg", "#292929", "#2F2F2F", "#232323");;
	cancelButton->setFixedHeight(32);
	cancelButton->setIconSize(QSize(18, 18));

	saveCancelLayout->addWidget(setTimerButton);

	saveCancelLayout->addWidget(cancelButton);

	setTimerWindowVLayout->addSpacing(24);

	QWidget* separatingLine = new QWidget(TimerWindowClass);
	separatingLine->setStyleSheet("background-color: #191919;");
	separatingLine->setFixedSize(TimerWindowClass->maximumWidth(), 1);

	separatingLine->move(0, 310);

	setTimerWindowVLayout->addSpacing(24);

	setTimerWindowVLayout->addLayout(saveCancelLayout);

	TimerWindowClass->setLayout(setTimerWindowVLayout);

	QMetaObject::connectSlotsByName(TimerWindowClass);
}

void TimerWindowUI::setupEditTimerWindowUI(QDialog* TimerWindowClass)
{
	setupAddTimerWindowUI(TimerWindowClass);

	title->setText("Edit timer");

	deleteButton = new IconPushButton(TimerWindowClass, "", "transparent", "transparent", "Resources/delete-grey.svg", "Resources/delete-grey.svg", "transparent", "#302c2c", "#282424");
	deleteButton->setFixedSize(32, 32);

	deleteButton->move(290, 10);
}

void TimerWindowUI::setValues(const QString& name, const QTime& time)
{
	hoursSpinBox->setValue(time.hour());
	minutesSpinBox->setValue(time.minute());
	secondsSpinBox->setValue(time.second());

	nameLineEdit->setText(name);
}
