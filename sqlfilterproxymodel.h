#ifndef FILTER_H
#define FILTER_H

#include <QSortFilterProxyModel>

class SqlFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit SqlFilterProxyModel (QObject* parent = nullptr);
    void resize();
    QStringList getFilterData() { return fData; }
    void filterData(int column, const QString& filter);

    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const;
    
    QStringList fData;
};

#endif // FILTER_H
