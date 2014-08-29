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

    //Functions that determine the size of the widget
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void draw(int size);

private:
    const int WIDTH = 100;
    const int HEIGHT = 100;

    int lineXSize, lineYSize;
protected:
    void paintEvent(QPaintEvent* );

};

#endif // DRAWAREA_H
