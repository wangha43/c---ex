#include <QApplication>
#include "myserver.h"
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog di;
    di.show();
    return a.exec();
}
