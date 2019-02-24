#include "mainGUI.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainGUI gui;
    gui.move(100, 100);
    gui.show();
    return a.exec();
}
