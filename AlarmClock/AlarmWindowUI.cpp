#include "AlarmWindowUI.h"

AlarmWindowUI::AlarmWindowUI()
{
	QSettings settings(settingsFile, QSettings::IniFormat);
	defaultNameCounter = settings.value("defaultNameCounter", 0).toInt();
}

AlarmWindowUI::~AlarmWindowUI()
{
	QSettings settings(settingsFile, QSettings::IniFormat);
	settings.setValue("defaultNameCounter", defaultNameCounter);
}

void AlarmWindowUI::setupAddAlarmWindowUI(QDialog* AlarmWindowClass)
{
	AlarmWindowClass->setStyleSheet("background-color: #201c1c; border: none;");

	setAlarmWindowVLayout = new QVBoxLayout(AlarmWindowClass);
	setAlarmWindowVLayout->setContentsMargins(30, 30, 30, 30);

	title = new QLabel("Add a new alarm clock");
	title->setStyleSheet("color: white; font-size: 20px; font-weight: bold;");

	setAlarmWindowVLayout->addWidget(title);

	timeWrapperWidget = new TimeWrapperWidget(AlarmWindowClass, "#383434", activeAccentColor);
	timeWrapperWidget->setFixedSize(272, 80);

	timeSelectorWidget = new TimeWrapperChildWidget(timeWrapperWidget, "#201c1c", "transparent");
	timeSelectorWidget->setFixedSize(266, 74);

	timeSelectorWidget->move((timeWrapperWidget->width() - timeSelectorWidget->width()) / 2, (timeWrapperWidget->height() - timeSelectorWidget->height()) / 2);

	timeSelectorHBoxLayout = new QHBoxLayout(timeSelectorWidget);
	timeSelectorHBoxLayout->setContentsMargins(38, 2, 38, 2);

	hoursSpinBox = new TimeSpinBox(timeSelectorWidget, 0, 23);
	hoursSpinBox->setFixedSize(70, 70);
	minutesSpinBox = new TimeSpinBox(timeSelectorWidget, 0, 59);
	minutesSpinBox->setFixedSize(70, 70);

	timeSelectorHBoxLayout->addWidget(hoursSpinBox);

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

	editNameHBoxLayout = new QHBoxLayout(AlarmWindowClass);

	QHBoxLayout* arrowsUpLayout = new QHBoxLayout(AlarmWindowClass);
	QHBoxLayout* arrowsDownLayout = new QHBoxLayout(AlarmWindowClass);

	arrowsUpLayout->setContentsMargins(60, 0, 60, 0);
	arrowsDownLayout->setContentsMargins(60, 0, 60, 0);

	arrowUpButton1 = new ArrowPushButton(AlarmWindowClass, true);
	arrowUpButton1->setFixedSize(32, 32);

	QObject::connect(arrowUpButton1, &QPushButton::pressed, [&]() {
		hoursSpinBox->setValue(hoursSpinBox->value() + 1);
		hoursSpinBox->setFocus();
		});

	arrowUpButton2 = new ArrowPushButton(AlarmWindowClass, true);
	arrowUpButton2->setFixedSize(32, 32);

	QObject::connect(arrowUpButton2, &QPushButton::pressed, [&]() {
		minutesSpinBox->setValue(minutesSpinBox->value() + 1);
		minutesSpinBox->setFocus();
		});

	arrowDownButton1 = new ArrowPushButton(AlarmWindowClass, false);
	arrowDownButton1->setFixedSize(32, 32);

	QObject::connect(arrowDownButton1, &QPushButton::pressed, [&]() {
		hoursSpinBox->setValue(hoursSpinBox->value() - 1);
		hoursSpinBox->setFocus();
		});

	arrowDownButton2 = new ArrowPushButton(AlarmWindowClass, false);
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

	QVBoxLayout* timeSelectorLayout = new QVBoxLayout(AlarmWindowClass);

	setAlarmWindowVLayout->addSpacing(13);

	setAlarmWindowVLayout->addLayout(arrowsUpLayout);
	setAlarmWindowVLayout->addWidget(timeWrapperWidget);
	setAlarmWindowVLayout->addLayout(arrowsDownLayout);

	editSvgWidget = new QSvgWidget(AlarmWindowClass);
	editSvgWidget->load(QString("Resources/edit-white.svg"));
	editSvgWidget->setFixedSize(16, 16);

	editNameHBoxLayout->addWidget(editSvgWidget);

	editNameWrapperWidget = new TimeWrapperWidget(AlarmWindowClass, "#383434", activeAccentColor, false);
	editNameWrapperWidget->setFixedSize(247, 34);

	editNameWidget = new TimeWrapperChildWidget(editNameWrapperWidget, "#292929", "#2F2F2F");
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

	xButton = new XPushButton(editNameWidget);
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

	QObject::connect(xButton, &QPushButton::pressed, [&] {
		if (!nameLineEdit->text().isEmpty())
			nameLineEdit->clear();
		nameLineEdit->setFocus();
	});

	nameLineEditLayout->addWidget(nameLineEdit);
	nameLineEditLayout->addStretch(1);
	nameLineEditLayout->addWidget(xButton);

	editNameHBoxLayout->addWidget(editNameWrapperWidget);

	setAlarmWindowVLayout->addSpacing(14);

	setAlarmWindowVLayout->addLayout(editNameHBoxLayout);

	saveCancelLayout = new QHBoxLayout(AlarmWindowClass);

	setAlarmButton = new IconPushButton(AlarmWindowClass, "Save", "#07080a", "#37516a", "Resources/save-dark.svg", "Resources/save-light.svg", "#78bcec", "#70acdc", "#689cc4");
	setAlarmButton->setFixedHeight(32);
	setAlarmButton->setIconSize(QSize(18, 18));

	QObject::connect(setAlarmButton, &QPushButton::pressed, [&] {
		if (nameLineEdit->text() == (defaultName + " (" + QString::number(defaultNameCounter + 1) + ")"))
			defaultNameCounter++;
	});

	cancelButton = new IconPushButton(AlarmWindowClass, "Cancel", "white", "#a09c9c", "Resources/x-white.svg", "Resources/x-grey.svg", "#292929", "#2F2F2F", "#232323");;
	cancelButton->setFixedHeight(32);
	cancelButton->setIconSize(QSize(18, 18));

	saveCancelLayout->addWidget(setAlarmButton);

	saveCancelLayout->addWidget(cancelButton);

	setAlarmWindowVLayout->addSpacing(24);

	QWidget* separatingLine = new QWidget(AlarmWindowClass);
	separatingLine->setStyleSheet("background-color: #191919;");
	separatingLine->setFixedSize(AlarmWindowClass->maximumWidth(), 1);

	separatingLine->move(0, 310);

	setAlarmWindowVLayout->addSpacing(24);

	setAlarmWindowVLayout->addLayout(saveCancelLayout);

	AlarmWindowClass->setLayout(setAlarmWindowVLayout);

	QMetaObject::connectSlotsByName(AlarmWindowClass);
}

void AlarmWindowUI::setupEditAlarmWindowUI(QDialog* AlarmWindowClass)
{
	setupAddAlarmWindowUI(AlarmWindowClass);

	title->setText("Edit alarm clock");

	deleteButton = new IconPushButton(AlarmWindowClass, "", "transparent", "transparent", "Resources/delete-grey.svg", "Resources/delete-grey.svg", "transparent", "#302c2c", "#282424");
	deleteButton->setFixedSize(32, 32);

	deleteButton->move(290, 10);

	QObject::connect(deleteButton, &QPushButton::clicked, [&] {
		if (initialName == (defaultName + " (" + QString::number(defaultNameCounter) + ")"))
			defaultNameCounter--;
	});
}

void AlarmWindowUI::setDefaultTime()
{
	hoursSpinBox->setValue(7);
	minutesSpinBox->setValue(0);
}

void AlarmWindowUI::setDefaultName()
{
	nameLineEdit->setText(defaultName + " (" + QString::number(defaultNameCounter + 1) + ")");
}

void AlarmWindowUI::setValues(const QString& name, const QTime& time)
{
	hoursSpinBox->setValue(time.hour());
	minutesSpinBox->setValue(time.minute());

	initialName = name;
	nameLineEdit->setText(name);
}
