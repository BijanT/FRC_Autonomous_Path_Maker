#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QSize>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <cmath>
#include <QDebug>

#define PI 3.14159265

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

    QPoint endOfLastLine, endOfNewLine;
protected:
    void paintEvent(QPaintEvent* );

};

#endif // DRAWAREA_H
