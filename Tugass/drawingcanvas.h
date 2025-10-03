#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QVector>
#include <QPoint>

class DrawingCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

public slots:
    void clearCanvas();
    void runSlowConvexHull();
    void runFastConvexHull();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QVector<QPoint> m_points;
    QVector<QPoint> m_hullPoints;
    QString m_hullAlgorithm;
    int m_iterations;
    int orientation(QPoint p, QPoint q, QPoint r);

    void slowConvexHull(const QVector<QPoint>& points);
    void fastConvexHull(const QVector<QPoint>& points);
};

#endif
