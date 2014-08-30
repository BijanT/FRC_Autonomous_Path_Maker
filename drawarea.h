#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QSize>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <cmath>
#include <QDebug>
#include <vector>

#define PI 3.14159265

struct PathLine
{
    QPoint lineStart;
    QPoint lineEnd;

    PathLine(QPoint start, QPoint end)
    {
        lineStart = start;
        lineEnd = end;
    }

    PathLine()
    {
        lineStart = QPoint(0, 0);
        lineEnd = QPoint(0, 0);
    }
};

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    DrawArea(QWidget* parent = 0);
    ~DrawArea();

    void draw(int direction, int distance);

private:
    const int WIDTH = 620;
    const int HEIGHT = 450;

    std::vector< PathLine > lines;

protected:
    void paintEvent(QPaintEvent* );

};

#endif // DRAWAREA_H
