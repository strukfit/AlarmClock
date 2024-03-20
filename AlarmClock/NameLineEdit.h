#pragma once

#include <QLineEdit>

#include "TimeWrapperWidget.h"

class NameLineEdit : public QLineEdit
{
public:
	NameLineEdit(QWidget* parent);
	~NameLineEdit();

protected:
	void focusInEvent(QFocusEvent* event) override;
	void focusOutEvent(QFocusEvent* event) override;
};