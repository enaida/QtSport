#include "mainwindow.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1400,800);
    w.setBackground(":/images/background.jpg");
    w.show();
    w.setPlayersCombo();
    return a.exec();
}
