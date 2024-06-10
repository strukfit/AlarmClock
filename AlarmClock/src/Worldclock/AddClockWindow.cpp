#include "Worldclock/AddClockWindow.h"

AddClockWindow::AddClockWindow(QWidget* parent): 
	QDialog(parent),
	ui(new Ui::AddClockWindowClass)
{
	ui->setupUI(this);
	ui->locationSearchBar->setFixedWidth(312);

	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_DeleteOnClose);

	connect(ui->addButton, &QPushButton::clicked, this, [&] {
		if (ui->locationSearchBar->isValid())
			emit setClock(ClockWidget::lastId + 1, ui->locationSearchBar->getLocation().toUtf8());

		close();
	});

	connect(ui->cancelButton, &QPushButton::clicked, this, [&] {
		close();
	});
}

AddClockWindow::~AddClockWindow() 
{
	delete ui;
}

void AddClockWindow::setFocus()
{
	ui->locationSearchBar->setFocus();
}
