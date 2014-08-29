#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QSize>
#include <QPainter>
#include <QPen>

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    DrawArea(QWidget* parent = 0);
    ~DrawArea();

    void draw(int size);

private:
    const int WIDTH = 620;
    const int HEIGHT = 450;

    int lineXSize, lineYSize;
protected:
    void paintEvent(QPaintEvent* );

};

#endif // DRAWAREA_H
