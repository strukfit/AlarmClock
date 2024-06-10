#pragma once

#include <QDialog>
#include <QMessageBox>

#include "Worldclock/AddClockWindowUI.h"
#include "Worldclock/ClockWidget.h"

class AddClockWindow : public QDialog
{
	Q_OBJECT

signals:
	void setClock(const int& id, const QByteArray& timeZoneId);

public:
	AddClockWindow(QWidget* parent = nullptr);
	~AddClockWindow();

	void setFocus();

private:
	Ui::AddClockWindowClass* ui;
};