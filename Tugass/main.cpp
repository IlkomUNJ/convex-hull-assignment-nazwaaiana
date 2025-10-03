// Nazwa aiana putri (1313623016)
#include "drawingwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawingWindow w;
    w.show();
    return a.exec();
}
