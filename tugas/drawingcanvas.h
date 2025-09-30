#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPoint>
#include <QVector>

class DrawingCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

    void calculateConvexHull();
    void clearCanvas();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<QPoint> m_points;
    QVector<QPoint> m_convexHull;
    QPoint findPivot(const QVector<QPoint>& points) const;
    int orientation(QPoint p, QPoint q, QPoint r) const;

    qreal distSq(QPoint p1, QPoint p2) const;

    static bool comparePoints(const QPoint& p1, const QPoint& p2, QPoint pivot);
};

#endif
