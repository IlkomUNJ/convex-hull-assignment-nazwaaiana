#include "drawingwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

DrawingWindow::DrawingWindow(QWidget *parent)
    : QMainWindow(parent),
    canvas(new DrawingCanvas(this))
{
    setupUI();
    setWindowTitle("Simulasi Convex Hull (Graham Scan)");
    resize(800, 600);
}

DrawingWindow::~DrawingWindow()
{}

void DrawingWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    mainLayout->addWidget(canvas, 1);
    calculateButton = new QPushButton("Convex Hull", this);
    clearButton = new QPushButton("Clear Canvas", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(calculateButton);
    buttonLayout->addWidget(clearButton);

    mainLayout->addLayout(buttonLayout);
    connect(calculateButton, &QPushButton::clicked, this, &DrawingWindow::on_calculateButton_clicked);
    connect(clearButton, &QPushButton::clicked, this, &DrawingWindow::on_clearButton_clicked);
}

void DrawingWindow::on_calculateButton_clicked()
{
    canvas->calculateConvexHull();
}

void DrawingWindow::on_clearButton_clicked()
{
    canvas->clearCanvas();
}
