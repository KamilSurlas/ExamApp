#include "mainwindow.h"
#include "MainApp.h"
#include <QApplication>
//ZMIANA
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainApp mainApp;
    MainWindow window(nullptr,&mainApp);
    window.show();
    return a.exec();
}
