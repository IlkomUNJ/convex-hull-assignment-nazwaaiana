#include "drawingcanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtAlgorithms>
#include <cmath>
#include <algorithm>

DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
}

QPoint DrawingCanvas::findPivot(const QVector<QPoint>& points) const
{
    if (points.isEmpty()) return QPoint();
    QPoint pivot = points.first();
    for (const QPoint& p : points) {
        if (p.y() < pivot.y() || (p.y() == pivot.y() && p.x() < pivot.x())) {
            pivot = p;
        }
    }
    return pivot;
}

int DrawingCanvas::orientation(QPoint p, QPoint q, QPoint r) const
{
    qreal val = (q.y() - p.y()) * (r.x() - q.x()) -
                (q.x() - p.x()) * (r.y() - q.y());

    if (qFuzzyIsNull(val)) return 0;
    return (val > 0) ? 1 : 2;
}

qreal DrawingCanvas::distSq(QPoint p1, QPoint p2) const
{
    return (p1.x() - p2.x()) * (p1.x() - p2.x()) +
           (p1.y() - p2.y()) * (p1.y() - p2.y());
}

bool DrawingCanvas::comparePoints(const QPoint& p1, const QPoint& p2, QPoint pivot)
{
    auto static_orientation = [](QPoint p, QPoint q, QPoint r) -> int {
        qreal val = (q.y() - p.y()) * (r.x() - q.x()) - (q.x() - p.x()) * (r.y() - q.y());
        if (qFuzzyIsNull(val)) return 0;
        return (val > 0) ? 1 : 2;
    };

    auto static_distSq = [](QPoint p1, QPoint p2) -> qreal {
        return (p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y());
    };

    int o = static_orientation(pivot, p1, p2);

    if (o == 0) {
        return (static_distSq(pivot, p1) < static_distSq(pivot, p2));
    }
    return (o == 2);
}

void DrawingCanvas::calculateConvexHull()
{
    m_convexHull.clear();

    if (m_points.size() < 3) {
        m_convexHull = m_points;
        update();
        return;
    }

    QPoint pivot = findPivot(m_points);
    int pivotIndex = m_points.indexOf(pivot);

    if (pivotIndex >= 0 && pivotIndex != 0) {
        std::swap(m_points[0], m_points[pivotIndex]);
    }

    std::sort(m_points.begin() + 1, m_points.end(),
              [pivot](const QPoint& p1, const QPoint& p2) {
                  return comparePoints(p1, p2, pivot);
              });

    QVector<QPoint> stack;
    stack.append(m_points[0]);
    stack.append(m_points[1]);

    for (int i = 2; i < m_points.size(); ++i) {
        while (stack.size() > 1 && orientation(stack[stack.size()-2], stack.last(), m_points[i]) != 2) {
            stack.pop_back();
        }
        stack.append(m_points[i]);
    }

    m_convexHull = stack;
    update();
}


void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_convexHull.clear();
        m_points.append(event->pos());
        update();
    }
}

void DrawingCanvas::clearCanvas()
{
    m_points.clear();
    m_convexHull.clear();
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pointPen(Qt::red, 8, Qt::SolidLine);
    painter.setPen(pointPen);

    for (const QPoint& point : m_points) {
        painter.drawPoint(point);
    }

    if (m_convexHull.size() > 1) {
        QPen hullPen(Qt::blue, 3, Qt::SolidLine);
        painter.setPen(hullPen);
        painter.setBrush(Qt::NoBrush);

        QPolygon hullPolygon;
        for (const QPoint& p : m_convexHull) {
            hullPolygon << p;
        }

        painter.drawPolygon(hullPolygon);
    }
}
