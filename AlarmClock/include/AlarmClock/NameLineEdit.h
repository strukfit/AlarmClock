#pragma once

#include <QLineEdit>
#include <QTimer>

#include "TimeWrapperWidget.h"

class NameLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	NameLineEdit(QWidget* parent);
	~NameLineEdit();

signals:
	void focusGained();
	void focusLost();

protected:
	void focusInEvent(QFocusEvent* event) override;
	void focusOutEvent(QFocusEvent* event) override;
};