#include "sqlfilterproxymodel.h"

SqlFilterProxyModel::SqlFilterProxyModel(QObject* parent)
	: QSortFilterProxyModel(parent)
{

}

void SqlFilterProxyModel::resize()
{
    fData.clear();

    while (fData.size() < sourceModel()->columnCount()) {
        fData.append("");
    }
}


void SqlFilterProxyModel::filterData(int column, const QString& filter) {
    if (fData.size() < column) {
        return;
    }

    fData[column] = filter;

    invalidateFilter();
}

bool SqlFilterProxyModel::filterAcceptsRow(int sourceRow,
    const QModelIndex& sourceParent) const
    
{
    if (!sourceRow) {
        return true;
    }


    if (fData.size() == sourceModel()->columnCount()) {
        for (int i = 0; i < sourceModel()->columnCount(); i++)
        {
            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);

            if (!sourceModel()->data(index).toString().contains(fData[i]))
            {
                return false;
            }
        }
    }

    return true;


}
