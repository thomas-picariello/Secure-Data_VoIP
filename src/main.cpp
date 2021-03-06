#include <QApplication>
#include "svoip.h"
#include "flattouchstyle.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("FHNW-ICS");
    QCoreApplication::setApplicationName("SVoIP");
    QCoreApplication::setApplicationVersion("0.1");
    app.setStyle(new FlatTouchStyle());

    SVoIP svoip;

    return app.exec();
}
