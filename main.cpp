#include "gameOfLifeWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameOfLIfeWindow w;
    w.show();

    return a.exec();
}
