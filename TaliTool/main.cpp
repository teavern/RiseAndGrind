#include "talitool.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaliTool w;
    w.show();
    return a.exec();
}
