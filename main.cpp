#include <QApplication>
#include "icrandomizer.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icrandomizer);

    QApplication app(argc, argv);
    Randomizer randomizer;
    randomizer.show();
    return app.exec();
}
