#ifndef DRAWINGWINDOW_H
#define DRAWINGWINDOW_H

#include <QMainWindow>
#include "drawingcanvas.h"
#include <QPushButton>

class DrawingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawingWindow(QWidget *parent = nullptr);
    ~DrawingWindow();

private slots:
    void on_calculateButton_clicked();
    void on_clearButton_clicked();

private:
    DrawingCanvas *canvas;
    QPushButton *calculateButton;
    QPushButton *clearButton;

    void setupUI();
};

#endif
