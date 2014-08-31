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

    PathLine(QPoint start, QPoint end) :
        lineStart(start), lineEnd(end)
    {
    }

    PathLine()
    {
        lineStart = QPoint(0, 0);
        lineEnd = QPoint(0, 0);
    }
};

struct PathInstruction
{
    int direction;
    int distance;

    PathInstruction(int dir, int dis) :
        direction(dir), distance(dis)
    {
    }
};

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    DrawArea(QWidget* parent = 0);
    ~DrawArea();

    void draw(int direction, int distance);
    void clearScreen();
    void removeLastLine();

    std::vector< PathInstruction > getInstructions(){return instructions;}

private:
    const int WIDTH = 620;
    const int HEIGHT = 450;

    std::vector< PathLine > lines;
    std::vector< PathInstruction> instructions;

protected:
    void paintEvent(QPaintEvent* );

};

#endif // DRAWAREA_H
