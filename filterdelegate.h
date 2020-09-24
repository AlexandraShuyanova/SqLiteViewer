#pragma once

#include <QStyledItemDelegate>
#include <QLineEdit>

class FilterDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    FilterDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    ~FilterDelegate() {}

    void resize(int size);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setParentWidget(QWidget* parentWidget) { this->parentWidget = parentWidget; }

private:
    QStringList filters;
    mutable int currentColumn;
    QWidget* parentWidget = nullptr;

private slots:
    void dataChanged(const QString& text);

signals:
    void filterTextChanged(int column, const QString& text);
};

class FilterLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    FilterLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) {}

protected:
    void focusInEvent(QFocusEvent* e)
    {
        QLineEdit::focusInEvent(e);
        deselect();
    }
};

