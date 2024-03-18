#include <QtWidgets/QApplication>
#include <QFont>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    //QFont defaultFont("RobotoSlab-Regular");
    //a.setFont(defaultFont);

    MainWindow w;
    w.show();
    return a.exec();
}
