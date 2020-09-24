#include "sqlliteitemmodel.h"
#include <QFont>
#include <QBrush>
#include <QFileSystemModel>
#include "sqlliteviewer.h"


SqlLiteItemModel::SqlLiteItemModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

void SqlLiteItemModel::appendData(const QList<QStringList>& data) {
    if (tableData == data)
    {
        return;
    }

    bool isReset = false;

    int removeFirstColumn = 0;
    int removeLastColumn = 0;
    bool isRemoveColumns = false;
    int insertFirstColumn = 0;
    int insertLastColumn = 0;
    bool isInsertColumns = false;

    int removeFirstRow = 0;
    int removeLastRow = 0;
    bool isRemoveRows = false;
    int insertFirstRow = 0;
    int insertLastRow = 0;
    bool isInsertRows = false;

    if (!tableData.size() || !data.size())
    {
        isReset = true;
    }

    if (data.size() < tableData.size())
    {
        isRemoveRows = true;
        removeFirstRow = data.size() + 1;
        removeLastRow = tableData.size();
    }

    if (data.size() > tableData.size())
    {
        isInsertRows = true;
        insertFirstRow = tableData.size() + 1;
        insertLastRow = data.size();
    }

    int dataColumns = data.size() ? data.first().size() : 0;
    int tableDataColumns = tableData.size() ? tableData.first().size() : 0;

    if (dataColumns < tableDataColumns)
    {
        isRemoveColumns = true;
        removeFirstColumn = dataColumns;
        removeLastColumn = tableDataColumns - 1;
    }

    if (dataColumns > tableDataColumns)
    {
        isInsertColumns = true;
        insertFirstColumn = tableDataColumns;
        insertLastColumn = dataColumns - 1;
    }

    if (isReset)
    {
        emit beginResetModel();
        tableData = data;
        emit endResetModel();
    }
    else
    {
        if (isRemoveColumns)
        {
            beginRemoveColumns(QModelIndex(), removeFirstColumn, removeLastColumn);

            int count = removeLastColumn - removeFirstColumn + 1;

            for (auto& column : tableData) {
                for (int i = count; i > 0; i--) {
                    column.removeAt(column.size() - 1);
                }
            }

            endRemoveColumns();
        }

        if (isInsertColumns)
        {
            beginInsertColumns(QModelIndex(), insertFirstColumn, insertLastColumn);

            int count = insertLastColumn - insertFirstColumn + 1;

            for (auto& column : tableData) {
                for (int i = count; i > 0; i--) {
                    column.append(QString());
                }
            }

            endInsertColumns();
        }

        if (isRemoveRows)
        {
            beginRemoveRows(QModelIndex(), removeFirstRow, removeLastRow);

            int count = removeLastRow - removeFirstRow + 1;

            for (int i = count; i > 0; i--) {
                tableData.removeAt(tableData.size() - 1);
            }

            endRemoveRows();
        }
        if (isInsertRows)
        {
            beginInsertRows(QModelIndex(), insertFirstRow, insertLastRow);

            int count = insertLastRow - insertFirstRow + 1;

            for (int i = count; i > 0; i--) {
                QStringList list;

                for (int i = 0; i < columnCount(); i++) {
                    list.append(QString());
                }

                tableData.append(list);
            }

            endInsertRows();
        }

        tableData = data;

        QModelIndex topLeft = index(0, 0);
        QModelIndex bottomRight = index(data.size() - 1, data.last().size() - 1);
        emit dataChanged(topLeft, bottomRight);
    }
};

void SqlLiteItemModel::appendHeaderData(const QStringList &headerData) {
    tableHeaderData = headerData;

    /*if (headerData.size())
    {
        emit headerDataChanged(Qt::Horizontal, 0, headerData.size() - 1);
    }*/
};


QVariant SqlLiteItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {

        if (section < 0 || section >= tableHeaderData.size()) {
            return QVariant();
        }

        return tableHeaderData[section];

    } else if (role == Qt::DisplayRole && orientation == Qt::Vertical && section > 0) {

        return QString::number(section);

    }

    return QVariant();
}


QModelIndex SqlLiteItemModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!

    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

QModelIndex SqlLiteItemModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int SqlLiteItemModel::rowCount(const QModelIndex & /*parent*/) const
{
    return tableData.size() + 1;
}

int SqlLiteItemModel::columnCount(const QModelIndex & /*parent*/) const
{
    if (!tableData.size()) {
        return 0;
    }

    return tableData.first().size();
}

QVariant SqlLiteItemModel::data(const QModelIndex& index, int role) const
{
   
    int row = index.row() - 1;
    int col = index.column();

    if (role == Qt::DisplayRole && row >= 0) {

        return tableData[row][col];
    }

    return QVariant();
}

Qt::ItemFlags SqlLiteItemModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;
    flags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    if (index.row() == 0)
    {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}
