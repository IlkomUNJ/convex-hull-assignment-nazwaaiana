#include "drawingwindow.h"
#include "drawingcanvas.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

DrawingWindow::DrawingWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Convex Hull Simulation");
    resize(600, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QHBoxLayout *hlayout = new QHBoxLayout();

    DrawingCanvas *canvas = new DrawingCanvas(this);
    layout->addWidget(canvas, 1);

    QPushButton *slowHullButton = new QPushButton("Run Slow Hull");
    QPushButton *fastHullButton = new QPushButton("Run Fast Hull");
    QPushButton *clearButton = new QPushButton("Clear Canvas");

    hlayout->addWidget(slowHullButton, 1);
    hlayout->addWidget(fastHullButton, 1);
    hlayout->addWidget(clearButton, 0);
    layout->addLayout(hlayout, 0);

    connect(slowHullButton, &QPushButton::clicked, canvas, &DrawingCanvas::runSlowConvexHull);
    connect(fastHullButton, &QPushButton::clicked, canvas, &DrawingCanvas::runFastConvexHull);
    connect(clearButton, &QPushButton::clicked, canvas, &DrawingCanvas::clearCanvas);

}
