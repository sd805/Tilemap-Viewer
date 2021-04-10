#include "tilemap.h"

#include <QApplication>
#include "Magick++.h"

int main(int argc, char *argv[])
{
    Magick::InitializeMagick(*argv);
    QApplication a(argc, argv);
    Tilemap w;
    w.show();
    return a.exec();
}
