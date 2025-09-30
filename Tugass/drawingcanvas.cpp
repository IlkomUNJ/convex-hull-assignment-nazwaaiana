#include "drawingcanvas.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QSet>
#include <algorithm>

using namespace std;

struct PointComparer {
    bool operator()(const QPoint& a, const QPoint& b) const {
        if (a.x() != b.x()) {
            return a.x() < b.x();
        }
        return a.y() < b.y();
    }
};

DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget(parent), m_iterations(0), m_hullAlgorithm("None")
{}

void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::blue, 6, Qt::SolidLine));
    for (const QPoint& p : m_points) {
        painter.drawPoint(p);
    }

    if (m_hullPoints.size() > 1) {
        painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
        painter.drawPolyline(m_hullPoints.data(), m_hullPoints.size());

        if (m_hullPoints.size() > 2) {
            painter.drawLine(m_hullPoints.last(), m_hullPoints.first());
        }

        painter.setPen(QPen(Qt::red, 8, Qt::SolidLine));
        for (const QPoint& p : m_hullPoints) {
            painter.drawPoint(p);
        }
    }

    painter.setPen(Qt::yellow);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, "Input Points: " + QString::number(m_points.size()));
    painter.drawText(10, 40, "Algoritma: " + m_hullAlgorithm);
    painter.drawText(10, 60, "Iterasi: " + QString::number(m_iterations));
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_hullPoints.clear();
        m_points.append(event->pos());
        update();
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        m_hullPoints.clear();
        m_points.append(event->pos());
        update();
    }
}

void DrawingCanvas::clearCanvas()
{
    m_points.clear();
    m_hullPoints.clear();
    m_iterations = 0;
    m_hullAlgorithm = "None";
    update();
}

int DrawingCanvas::orientation(QPoint p, QPoint q, QPoint r)
{
    long long val = (long long)(q.y() - p.y()) * (r.x() - q.x()) -
                    (long long)(q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

void DrawingCanvas::slowConvexHull(const QVector<QPoint>& points)
{
    m_hullPoints.clear();
    m_iterations = 0;

    int n = points.size();
    if (n < 3) {
        m_hullPoints = points;
        return;
    }

    QSet<QPoint> hullCandidates;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            bool allRightOrCollinear = true;

            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                m_iterations++;

                int orient = orientation(points[i], points[j], points[k]);

                if (orient == 2) {
                    allRightOrCollinear = false;
                    break;
                }
            }

            if (allRightOrCollinear) {
                hullCandidates.insert(points[i]);
                hullCandidates.insert(points[j]);
            }
        }
    }

    QVector<QPoint> sortedPoints = hullCandidates.values();
    if (sortedPoints.size() < 3) {
        m_hullPoints = sortedPoints;
        return;
    }

    int l = 0;
    for (int i = 1; i < sortedPoints.size(); i++) {
        if (sortedPoints[i].x() < sortedPoints[l].x()) {
            l = i;
        }
    }

    int p = l, q;
    m_hullPoints.clear();

    do {
        m_hullPoints.append(sortedPoints[p]);
        q = (p + 1) % sortedPoints.size();

        for (int i = 0; i < sortedPoints.size(); i++) {
            if (orientation(sortedPoints[p], sortedPoints[i], sortedPoints[q]) == 2)
                q = i;
        }
        p = q;
    } while (p != l);
}

void DrawingCanvas::fastConvexHull(const QVector<QPoint>& points)
{
    m_hullPoints.clear();
    m_iterations = 0;

    int n = points.size();
    if (n < 3) {
        m_hullPoints = points;
        return;
    }

    QVector<QPoint> P = points;
    std::sort(P.begin(), P.end(), PointComparer());

    int final_n = P.size();

    QVector<QPoint> upperHull;
    for (int i = 0; i < final_n; ++i) {
        m_iterations++;
        while (upperHull.size() >= 2 && orientation(upperHull[upperHull.size()-2], upperHull.last(), P[i]) != 2)
        {
            m_iterations++;
            upperHull.pop_back();
        }
        upperHull.push_back(P[i]);
    }

    QVector<QPoint> lowerHull;
    for (int i = final_n - 1; i >= 0; --i) {
        m_iterations++;
        while (lowerHull.size() >= 2 && orientation(lowerHull[lowerHull.size()-2], lowerHull.last(), P[i]) != 2)
        {
            m_iterations++;
            lowerHull.pop_back();
        }
        lowerHull.push_back(P[i]);
    }

    m_hullPoints = upperHull;
    for (int i = 1; i < lowerHull.size() - 1; ++i) {
        m_hullPoints.push_back(lowerHull[i]);
    }
}

void DrawingCanvas::runSlowConvexHull()
{
    slowConvexHull(m_points);
    m_hullAlgorithm = "Slow Convex Hull";
    update();
}

void DrawingCanvas::runFastConvexHull()
{
    fastConvexHull(m_points);
    m_hullAlgorithm = "Fast Convex Hull";
    update();
}
