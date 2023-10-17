#include "mainwindow.h"
#include "Chat.h"

#include <QApplication>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = MainWindow::createClient();
    if (w)
        w->show();
    else
        return 0;
    return a.exec();
}
