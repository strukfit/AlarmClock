#pragma once

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QSize>
#include <QRect>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QEvent>
#include <QMessageBox>
#include "AlarmClockWidget.h"

class AlarmClockWidgetDelegate : public QStyledItemDelegate {
    Q_OBJECT

signals:
    void clicked(QModelIndex index) const;

public:
    AlarmClockWidgetDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        Q_UNUSED(painter);
        Q_UNUSED(option);
        Q_UNUSED(index);

        /*painter->save();
        QRect rect = option.rect;
        rect.adjust(48, 12, -48, -12);

        QBrush brush(Qt::red);
        painter->fillRect(rect, brush);
        painter->restore();*/

    }

    // Create Editor
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        Q_UNUSED(option);
        //AlarmClockWidget* widget = index.data(Qt::UserRole).value<AlarmClockWidget*>();

        /*AlarmClockWidget* widget = new AlarmClockWidget(parent, index.data(Qt::UserRole + 1).toInt(), index.data(Qt::UserRole + 2).value<QTime>(), index.data(Qt::UserRole + 3).toString());
        widget->setModelIndex(index);*/

        //QObject::connect(widget, &AlarmClockWidget::clicked, [&] {
        //    //emit clicked(alarm->getModelIndex());
        //    QMessageBox::information(nullptr, "", widget->getName());
        //});
        
        return index.data(Qt::UserRole).value<AlarmClockWidget*>();
    }

    void setEditorData(QWidget* editor, const QModelIndex& index) const override{
        Q_UNUSED(index);
        //AlarmClockWidget* widget = qobject_cast<AlarmClockWidget*>(editor);
    }

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override {
        Q_UNUSED(model);
        Q_UNUSED(index);
        Q_UNUSED(editor);
        //AlarmClockWidget* widget = static_cast<AlarmClockWidget*>(editor);
        //model->setData(index, widget->sizeHint(), Qt::SizeHintRole);

        /*AlarmClockWidget* widget = qobject_cast<AlarmClockWidget*>(editor);
        if (!widget)
        {
            QStyledItemDelegate::setModelData(editor, model, index);
            return;
        }*/
    }

    // Update Editor Geometry
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        Q_UNUSED(index);
        editor->setGeometry(option.rect.adjusted(48, 12, -48, -12));
    }

    // Size Hint
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        Q_UNUSED(option);
        Q_UNUSED(index);

        return QSize(733, 200);
        //return QSize(option.rect.width(), option.rect.height());
    }
};