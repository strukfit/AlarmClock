#include "AlarmClock/NameLineEdit.h"

NameLineEdit::NameLineEdit(QWidget* parent):
	QLineEdit(parent)
{
}

NameLineEdit::~NameLineEdit()
{
}

void NameLineEdit::focusInEvent(QFocusEvent* event)
{
    QLineEdit::focusInEvent(event);
    
    emit focusGained();

    QTimer::singleShot(0, this, &QLineEdit::selectAll);

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

    emit focusLost();

    if (parent() && parent()->parent()) {
        TimeWrapperWidget* wrapper = qobject_cast<TimeWrapperWidget*>(parent()->parent());
        if (wrapper)
            wrapper->childFocusOut();

        TimeWrapperChildWidget* wrapperChild = qobject_cast<TimeWrapperChildWidget*>(parentWidget());
        if (wrapperChild)
            wrapperChild->childFocusOut();
    }
}
