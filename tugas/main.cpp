// Nazwa Aiana Putri (1313623016)
// Tugas 1
#include <QApplication>
#include "drawingwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawingWindow w;
    w.show();
    return a.exec();
}
