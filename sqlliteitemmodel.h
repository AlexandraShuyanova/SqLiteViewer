#ifndef SQLLITEITEMMODEL_H
#define SQLLITEITEMMODEL_H

#include <QAbstractItemModel>

class SqlLiteItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SqlLiteItemModel(QObject *parent = nullptr);
    void appendHeaderData(const QStringList& headerData);
    void appendData(const QList <QStringList> &data);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    QList<QStringList> tableData;
    QStringList tableHeaderData;

private:
};

#endif // SQLLITEITEMMODEL_H
