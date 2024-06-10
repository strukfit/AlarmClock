#include "Worldclock/LocationSearchBar.h"

LocationSearchBar::LocationSearchBar(QWidget* parent)
{
	auto layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	lineEditWrapperWidget = new TimeWrapperWidget(this, "#383434", "#78bcec", false);
	lineEditWrapperWidget->setMinimumSize(247, 34);

	lineEditWidget = new TimeWrapperChildWidget(lineEditWrapperWidget, "#292929", "#2F2F2F");
	lineEditWidget->setMinimumSize(243, 30);

	lineEditWidget->move(2, 1);

	auto lineEditLayout = new QHBoxLayout(lineEditWidget);
	lineEditLayout->setContentsMargins(0, 1, 2, 0);

	lineEdit = new NameLineEdit(lineEditWidget);
	lineEdit->setMinimumSize(243, 28);

	lineEdit->setStyleSheet(R"(
		QLineEdit {
			color: white;
			font-size: 14px;
			background-color: transparent; 
			border: 0; 
			margin-left: 9px;
			margin-right: 35px;
			margin-bottom: 1px;
		}
		)");

	lineEdit->setPlaceholderText("Specify location");

	xButton = new IconPushButton(lineEditWidget, "", "", "", "Resources/x-grey.svg", "Resources/x-white.svg", "transparent", "#302c2c", "#282424");
	xButton->setFixedSize(29, 25);
	xButton->setFocusPolicy(Qt::NoFocus);
	xButton->hide();

	QObject::connect(lineEdit, &NameLineEdit::focusGained, [&] {
		if (!lineEdit->text().isEmpty())
			xButton->show();
		});

	QObject::connect(lineEdit, &NameLineEdit::focusLost, [&] {
		xButton->hide();
		});

	QObject::connect(lineEdit, &NameLineEdit::textChanged, [&] {
		if (!lineEdit->text().isEmpty())
			xButton->show();
		else
			xButton->hide();
		});

	QObject::connect(xButton, &QPushButton::clicked, [&] {
		if (!lineEdit->text().isEmpty())
			lineEdit->clear();
		lineEdit->setFocus();
		});

	lineEditLayout->addWidget(lineEdit);
	lineEditLayout->addStretch(1);
	lineEditLayout->addWidget(xButton);

	layout->addWidget(lineEditWrapperWidget);

	QStringList timeZoneIds;
	const auto& availableTimeZoneIds = QTimeZone::availableTimeZoneIds();
	for (const QByteArray& timeZoneId : availableTimeZoneIds)
	{
		timeZoneIds << QString(timeZoneId);
	}

	completer = new QCompleter(timeZoneIds, this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setFilterMode(Qt::MatchContains);
	completer->setCompletionMode(QCompleter::PopupCompletion);
	auto scrollBar = new CustomScrollBar(this);
	completer->popup()->setVerticalScrollBar(scrollBar);
	completer->popup()->setStyleSheet(R"(
		QAbstractItemView {
			background-color: #2c2c2c;
		}

		QAbstractItemView::item {
			height: 44px;
			font-size: 24px;
		}

		QAbstractItemView::item:hover {
			background-color: #383838;
		}
	)");

	lineEdit->setCompleter(completer);
}

void LocationSearchBar::setFixedWidth(int w)
{
	lineEditWrapperWidget->setFixedWidth(w);
	lineEditWidget->setFixedWidth(w-4);
	lineEdit->setFixedWidth(w-4);
}

void LocationSearchBar::setFocus()
{
	lineEdit->setFocus();
}

bool LocationSearchBar::isEmpty()
{
	return lineEdit->text().isEmpty();
}

bool LocationSearchBar::isValid()
{
	if (isEmpty())
		return false;

	QString text = lineEdit->text();

	completer->setCompletionPrefix(text);

	QModelIndex index = completer->completionModel()->index(0, 0);
	if (index.isValid())
	{
		QString completion = completer->completionModel()->data(index).toString();
		return completion == text;
	}

	return false;
}

QString LocationSearchBar::getLocation()
{
	return lineEdit->text();
}
