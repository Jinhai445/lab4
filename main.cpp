#include "masterview.h"

#include <QApplication>
#include "loginview.h"
#include "welcomeview.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f("宋体",9);
    a.setFont(f);
    MasterView w;
    w.show();
    return a.exec();
}
