/********************************************************************************
** Form generated from reading UI file 'sqlliteviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQLLITEVIEWER_H
#define UI_SQLLITEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "sqlliteviewer.h"

QT_BEGIN_NAMESPACE

class Ui_SqlLiteViewer
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QListWidget *menu;
    QTextEdit *footer;
    SqlTableView *sqlView;
    QTextEdit *header;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *SqlLiteViewer)
    {
        if (SqlLiteViewer->objectName().isEmpty())
            SqlLiteViewer->setObjectName(QString::fromUtf8("SqlLiteViewer"));
        SqlLiteViewer->resize(800, 781);
        actionOpen = new QAction(SqlLiteViewer);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralwidget = new QWidget(SqlLiteViewer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        menu = new QListWidget(centralwidget);
        menu->setObjectName(QString::fromUtf8("menu"));

        gridLayout->addWidget(menu, 0, 0, 3, 1);

        footer = new QTextEdit(centralwidget);
        footer->setObjectName(QString::fromUtf8("footer"));

        gridLayout->addWidget(footer, 2, 1, 1, 1);

        sqlView = new SqlTableView(centralwidget);
        sqlView->setObjectName(QString::fromUtf8("sqlView"));
        sqlView->setEnabled(true);

        gridLayout->addWidget(sqlView, 1, 1, 1, 1);

        header = new QTextEdit(centralwidget);
        header->setObjectName(QString::fromUtf8("header"));

        gridLayout->addWidget(header, 0, 1, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 5);
        gridLayout->setRowStretch(2, 2);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);
        SqlLiteViewer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SqlLiteViewer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        SqlLiteViewer->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(SqlLiteViewer);

        QMetaObject::connectSlotsByName(SqlLiteViewer);
    } // setupUi

    void retranslateUi(QMainWindow *SqlLiteViewer)
    {
        SqlLiteViewer->setWindowTitle(QCoreApplication::translate("SqlLiteViewer", "SqlLiteViewer", nullptr));
        actionOpen->setText(QCoreApplication::translate("SqlLiteViewer", "Open", nullptr));
        footer->setHtml(QCoreApplication::translate("SqlLiteViewer", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:600;\">Description</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This program allows you to open databases in SQLite format.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style="
                        "\" font-size:11pt; font-weight:600;\">Instruction</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1. Click File-&gt; Open;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2. Select DataBase file in dialog;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3. Select table;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4. Enter filters and press &quot;Find&quot; to filter your data.</p></body></html>", nullptr));
        menuFile->setTitle(QCoreApplication::translate("SqlLiteViewer", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SqlLiteViewer: public Ui_SqlLiteViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLLITEVIEWER_H
