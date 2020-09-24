#pragma once

#include <QtWidgets/QMainWindow>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QTableView>
#include "QtSql/QSqlDatabase"

namespace Ui {
    class SqlLiteViewer;
}

class SqlLiteItemModel;
class SqlFilterProxyModel;

class SqlLiteViewer : public QMainWindow
{
    Q_OBJECT

public:
    SqlLiteViewer(QWidget* parent = nullptr);
    
private:
    void updateTables();
    void updateHeader();

    Ui::SqlLiteViewer * ui;
    SqlLiteItemModel* model = nullptr;
    SqlFilterProxyModel* proxyModel = nullptr;
    QTimer* timer = nullptr;
    QString currentTable;
    QSqlDatabase db;
    QList<QString> dbTables;

private slots:
    void openDB();
    void openTable(QListWidgetItem* item);
    void filterTextChanged(int column, const QString& text);
    void updateTable();
};

class SqlTableView : public QTableView
{
    Q_OBJECT

public:
    SqlTableView(QWidget* parent = nullptr) : QTableView(parent) {}

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual bool event(QEvent* event);
};
