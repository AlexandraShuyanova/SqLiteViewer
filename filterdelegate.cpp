#include "filterdelegate.h"
#include <QPainter>

void FilterDelegate::resize(int size)
{
	while (filters.size() < size) {
		filters.append("");
	}
}

QWidget* FilterDelegate::createEditor(QWidget* parent,
	const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	currentColumn = index.column();
	FilterLineEdit* lineEdit = new FilterLineEdit(parent);
	connect(lineEdit, &FilterLineEdit::textChanged, this, &FilterDelegate::dataChanged);
	return lineEdit;
}

void FilterDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() >= filters.size()) {
		return;
	}

	FilterLineEdit line;
	line.setText(filters[index.column()]);
	line.setPlaceholderText("Filter...");

	painter->save();
	line.resize(option.rect.size());
	painter->translate(option.rect.topLeft());
	line.render(painter, QPoint(), QRegion(), QWidget::DrawChildren);
	painter->restore();
}

void FilterDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	FilterLineEdit* lineEdit = qobject_cast<FilterLineEdit*>(editor);
	lineEdit->setText(filters[index.column()]);
	lineEdit->setPlaceholderText("Filter...");
}

void FilterDelegate::dataChanged(const QString& text)
{
	filters[currentColumn] = text;
	emit filterTextChanged(currentColumn, text);
}
