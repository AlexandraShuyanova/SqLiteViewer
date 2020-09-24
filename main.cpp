#include "sqlliteviewer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SqlLiteViewer w;
    w.show();
    return a.exec();
}
