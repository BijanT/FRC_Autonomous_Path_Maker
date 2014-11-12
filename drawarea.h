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
    int speed; //The speed does not <i>need</i> to be saved in the draw area as it serves no purpose for drawing, but it is nice to keep the robot driving instructions together

    PathInstruction(int dir, int dis, int sp) :
        direction(dir), distance(dis), speed(sp)
    {
    }
};

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    DrawArea(QWidget* parent = 0);
    ~DrawArea();

    void draw(int direction, int distance, int speed);
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
