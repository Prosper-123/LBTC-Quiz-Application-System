#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Widget loginWidget;
    loginWidget.show();

    return app.exec();
}
