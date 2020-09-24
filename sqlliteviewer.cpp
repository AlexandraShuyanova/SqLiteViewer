#include "sqlliteviewer.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSqlQuery>
#include "ui_sqlliteviewer.h"
#include <QSortFilterProxyModel>
#include <QPushButton>
#include <QListWidget>
#include <QFont>
#include <QTextEdit>
#include <QTextCursor>
#include <QMouseEvent>
#include <QTimer>

#include "filterdelegate.h"
#include "sqlfilterproxymodel.h"
#include "sqlliteitemmodel.h"

SqlLiteViewer::SqlLiteViewer(QWidget* parent)
	: QMainWindow(parent),
	ui(new Ui::SqlLiteViewer)
{
	ui->setupUi(this);

	model = new SqlLiteItemModel(this);
	proxyModel = new SqlFilterProxyModel(this);
	
	proxyModel->setSourceModel(model);

	ui->sqlView->setModel(proxyModel);

	connect(ui->actionOpen, &QAction::triggered, this, &SqlLiteViewer::openDB);
	
	connect(ui->menu, &QListWidget::itemClicked, this, &SqlLiteViewer::openTable);
	ui->header->setReadOnly(true);
	ui->footer->setReadOnly(true);
	ui->sqlView->verticalHeader()->hide();
	ui->sqlView->setAttribute(Qt::WA_Hover);
	timer = new QTimer(this);
}

void SqlLiteViewer::openDB() {

	QString fileName = QFileDialog::getOpenFileName(this, "Open DB", "C://");
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(fileName);
	QMessageBox* msgBox = new QMessageBox(this);


	if (!db.open()) {
		msgBox->setText("Oops");
		msgBox->show();
		return;
	}

	connect(timer, &QTimer::timeout, this, &SqlLiteViewer::updateTable);
	timer->start(1000);
}


void SqlLiteViewer::updateTables() {

	if (dbTables == db.tables()) {
		return;
	}

	dbTables = db.tables();
	ui->menu->clear();
	model->appendData(QList<QStringList>());
	ui->header->clear();

	for (int i = 0; i < dbTables.size(); i++) {
		new QListWidgetItem(dbTables[i], ui->menu);
	}
}
   
void SqlLiteViewer::openTable(QListWidgetItem *item) {
	QSqlQuery query;

	currentTable = item->data(0).toString();
	query.exec(QString("pragma table_info({})").replace("{}", currentTable));

	updateHeader();
	 
	QStringList headerDataList;
	int columnNameIndex = 1;


	while (query.next()) {
		headerDataList.append(query.value(columnNameIndex).toString());
	}

	model->appendHeaderData(headerDataList);

	if (headerDataList.size())
	{
		FilterDelegate* filterDelegate = new FilterDelegate(this);
		filterDelegate->setParentWidget(ui->sqlView);
		filterDelegate->resize(headerDataList.size());
		ui->sqlView->setItemDelegateForRow(0, filterDelegate);
		connect(filterDelegate, &FilterDelegate::filterTextChanged, this, &SqlLiteViewer::filterTextChanged);
	}

	query.exec(QString("SELECT * FROM ({})").replace("{}", item->data(0).toString()));
	QList <QStringList> dataList;
	

	//Выводим значения из запроса
	while (query.next()) {
		QStringList list;
		for (int i = 0; i < headerDataList.size(); i++) {
			list.append(query.value(i).toString());
		}
		dataList.append(list);

	}

	model->appendData(dataList);	
	proxyModel->resize();
}

void SqlLiteViewer::updateHeader()
{
	ui->header->setPlainText(currentTable);
	QTextCursor cursor = ui->header->textCursor();
	ui->header->selectAll();
	QFont font;
	font.setBold(true);
	font.setWeight(32);

	ui->header->setFontPointSize(32);
	ui->header->setAlignment(Qt::AlignHCenter);
	ui->header->setTextCursor(cursor);
}

void SqlLiteViewer::filterTextChanged(int column, const QString& text)
{
	proxyModel->filterData(column, text);
}

void SqlTableView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		QModelIndex index = indexAt(event->pos());

		if (index.row() == 0) {
			edit(index);
		}
	}
}

bool SqlTableView::event(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::HoverEnter:
	case QEvent::HoverLeave:
	case QEvent::HoverMove:
		{
			QHoverEvent* hoverEvent = static_cast<QHoverEvent*>(event);
			
			QPoint position = hoverEvent->pos();
			position.setY(position.y() - horizontalHeader()->height());

			QModelIndex index = indexAt(position);

			if (index.row() == 0) {
				setCursor(Qt::IBeamCursor);
			}
			else {
				setCursor(Qt::ArrowCursor);
			}
		}
		break;
	default:
		break;
	}

	return QWidget::event(event);
}

void SqlLiteViewer::updateTable() {
	updateTables();

	if (currentTable.isEmpty()) {
		return;
	}

	bool isInList = false;

	for (int i = 0; i < ui->menu->count(); i++) {
		if (ui->menu->item(i)->data(Qt::DisplayRole).toString() == currentTable) {
			isInList = true;
			break;
		}
	}

	if (!isInList) {
		ui->header->clear();
		model->appendData(QList<QStringList>());

		QMessageBox* msgBox = new QMessageBox(this);
		msgBox->setIcon(QMessageBox::Warning);
		msgBox->setWindowTitle("Table removed");
		msgBox->setText("Table " + currentTable + " is removed!");
		msgBox->show();

		currentTable = QString();

		return;
	}

	updateHeader();

	QSqlQuery query;

	query.exec(QString("pragma table_info({})").replace("{}", currentTable));

	QStringList headerDataList;
	int columnNameIndex = 1;

	while (query.next()) {
		headerDataList.append(query.value(columnNameIndex).toString());
	}

	model->appendHeaderData(headerDataList);

	query.exec(QString("SELECT * FROM ({})").replace("{}", currentTable));
	QList <QStringList> dataList;


	//Выводим значения из запроса
	while (query.next()) {
		QStringList list;
		for (int i = 0; i < headerDataList.size(); i++) {
			list.append(query.value(i).toString());
		}
		dataList.append(list);

	}

	model->appendData(dataList);
	QStringList filtersData = proxyModel->getFilterData();
	proxyModel->resize();

	for (int i = 0; i < filtersData.size(); i++) {
		proxyModel->filterData(i, filtersData[i]);
	}

}
