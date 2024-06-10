#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStringList>
#include <QTimeZone>
#include <QByteArray>
#include <QString>
#include <QCompleter>
#include <QAbstractItemView>
	
#include "IconPushButton.h"
#include "AlarmClock/NameLineEdit.h"
#include "AlarmClock/TimeWrapperWidget.h"
#include "CustomScrollBar.h"

class LocationSearchBar : public QWidget {
public: 
	LocationSearchBar(QWidget* parent = nullptr);
	void setFixedWidth(int w);
	void setFocus();
	bool isEmpty();
	bool isValid();

	QString getLocation();

private: 
	TimeWrapperWidget* lineEditWrapperWidget;
	TimeWrapperChildWidget* lineEditWidget;
	NameLineEdit* lineEdit;
	IconPushButton* xButton;
	QCompleter* completer;
};