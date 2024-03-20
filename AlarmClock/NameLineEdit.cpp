#include "NameLineEdit.h"

NameLineEdit::NameLineEdit(QWidget* parent):
	QLineEdit(parent)
{
    setStyleSheet(R"(
        color: white;
        font-size: 14px;
        background-color: transparent; 
        border: 0; 
        margin-left: 8px; 
        margin-top: 1px; 
        margin-right: 33px; 
        margin-bottom: 0px;
    )");
}

NameLineEdit::~NameLineEdit()
{
}

void NameLineEdit::focusInEvent(QFocusEvent* event)
{
    QLineEdit::focusInEvent(event);
    this->selectAll();
    if (parent() && parent()->parent()) {
        TimeWrapperWidget* wrapper = qobject_cast<TimeWrapperWidget*>(parent()->parent());
        if (wrapper)
            wrapper->childFocusIn();

        TimeWrapperChildWidget* wrapperChild = qobject_cast<TimeWrapperChildWidget*>(parentWidget());
        if (wrapperChild)
            wrapperChild->childFocusIn();
    }
}

void NameLineEdit::focusOutEvent(QFocusEvent* event)
{
    QLineEdit::focusOutEvent(event);
    if (parent() && parent()->parent()) {
        TimeWrapperWidget* wrapper = qobject_cast<TimeWrapperWidget*>(parent()->parent());
        if (wrapper)
            wrapper->childFocusOut();

        TimeWrapperChildWidget* wrapperChild = qobject_cast<TimeWrapperChildWidget*>(parentWidget());
        if (wrapperChild)
            wrapperChild->childFocusOut();
    }
}
